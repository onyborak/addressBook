#include "bookclient.h"

#include <QFile>

BookClient::BookClient(QObject *parent)
	: QObject(parent)
{
	mSocket = new QTcpSocket(this);
	mStream.setDevice(mSocket);
	mStream.setVersion(QDataStream::Qt_5_7);
	connect(mSocket, &QTcpSocket::connected, this, [=](){
		requestBook();
		emit connectionChanged(true);
	});
	connect(mSocket, &QTcpSocket::disconnected, this, [=](){
		emit connectionChanged(false);
	});
	connect(mSocket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>
			(&QTcpSocket::error), this, [=](){
		emit clientError(QString("Ошибка сокета. " + mSocket->errorString()));
	});
	connect(mSocket, &QTcpSocket::readyRead, this, &BookClient::onReadyRead);
}

void BookClient::start(const QHostAddress &serverAddress, int serverPort)
{
	mSocket->connectToHost(serverAddress, serverPort);
}

void BookClient::sendBook(const QList<AddressBookRow> &book)
{
	QDomDocument doc("addressBook");
	QDomElement root = doc.createElement("Type");
	root.setAttribute("command", "set");
	doc.appendChild(root);

	QDomElement elem = doc.createElement("Book");
	root.appendChild(elem);

	foreach (AddressBookRow row, book)
	{
		QDomElement node = doc.createElement("Line");
		row.setNode(node);
		elem.appendChild(node);
	}

	mStream.startTransaction();
	mStream << doc.toByteArray();
	if (!mStream.commitTransaction())
	{
		emit clientError("Возникла ошибка отправки книги!");
	}
}

void BookClient::onReadyRead()
{
	QByteArray data;
	mStream.startTransaction();
	mStream >> data;
	if (!mStream.commitTransaction())
	{
		emit clientError("Возникла ошибка чтеня сообщения из сокета!");
		return;
	}
	if (data.isEmpty())
	{
		emit clientError("От сервера ничего не получили, видимо у него пока нет книги");
		return;
	}

	QDomDocument doc;
	QString errorStr;
	int errorLine = 0, errorColumn = 0;
	if (!doc.setContent(data, &errorStr, &errorLine, &errorColumn))
	{
		emit clientError(QString("Синтаксическая ошибка в принятом сообщении. Строка - %1, столбец - %2, ошибка: %3").arg(errorLine)
						 .arg(errorColumn).arg(errorStr));
		return;
	}

	QDomNode root = doc.firstChild();
	if (root.toElement().tagName() != "Book")
	{
		emit clientError("Не правильный формат принятого сообшения");
		return;
	}

	QDomNode node = root.firstChild();
	QList<AddressBookRow> adrBook;
	while (!node.isNull())
	{
		adrBook.append(AddressBookRow(node));
		node = node.nextSibling();
	}
	emit newBook(adrBook);

}

void BookClient::requestBook()
{
	QDomDocument doc("addressBook");
	QDomElement root = doc.createElement("Type");
	root.setAttribute("command", "get");
	doc.appendChild(root);
	mStream.startTransaction();
	mStream << doc.toByteArray();
	if (!mStream.commitTransaction())
	{
		emit clientError("Возникла отправки сообщения о запросе адресной книги!");
	}
}
