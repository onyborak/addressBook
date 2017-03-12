#include "oneconnection.h"
#include "core.h"

#include <QTcpSocket>
#include <QByteArray>

OneConnection::OneConnection(quintptr discriptor, QObject *parent)
	: QObject(parent)
{
	mSocket = new QTcpSocket(this);
	mSocket->setSocketDescriptor(discriptor);
	mStream.setDevice(mSocket);
	mStream.setVersion(QDataStream::Qt_5_7);
}

void OneConnection::start()
{
	connect(mSocket, &QTcpSocket::readyRead, this, &OneConnection::onReadyRead);
	connect(mSocket, &QTcpSocket::disconnected, this, &OneConnection::connectingLost);
}

void OneConnection::onReadyRead()
{
	QByteArray data;
	mStream.startTransaction();
	mStream >> data;
	if (!mStream.commitTransaction())
	{
		qDebug()<<"При чтении с сокета возникли ошибки";
		return;
	}

	QDomDocument doc;

	QString errorStr;
	int errorLine = 0, errorColumn = 0;
	if (!doc.setContent(data, &errorStr, &errorLine, &errorColumn))
	{
		qDebug()<<"Синтаксическая ошибка в принятом сообщении. Строка -"<<errorLine<<"столбец -"
			   <<errorColumn<<"ошибка:"<<errorStr;
		return;
	}

	QDomNode root = doc.firstChild();
	parseMessage(root);
}

void OneConnection::parseMessage(QDomNode &node)
{
	if (node.toElement().tagName() != "type" || node.isNull())
	{
		qDebug()<<"Не верное сообщение!";
		return;
	}

	if (node.toElement().attribute("command") == "get")
	{
		sendBook();
	}
	else if (node.toElement().attribute("command") == "set")
	{
		saveBook(node.firstChild());
	}

}

void OneConnection::saveBook(const QDomNode &node)
{
	Core::instance()->setBook(node);
}

void OneConnection::sendBook()
{
	QDomDocument book = Core::instance()->book().toDocument();
	if (mSocket->write(book.toByteArray()) == -1)
	{
		qDebug()<<"Ошибка отправки адрессной книги!"<<mSocket->errorString();
		return;
	}
}

