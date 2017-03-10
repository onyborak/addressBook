#include "oneconnection.h"

#include <QTcpSocket>
#include <QByteArray>
#include <QMutex>

QDomDocument OneConnection::mBook;

QMutex mutex;

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
}

void OneConnection::sendBook()
{
	QMutexLocker locker(&mutex);
	if (mSocket->write(mBook.toByteArray()) == -1)
	{
		qDebug()<<"Ошибка отправки адрессной книги!"<<mSocket->errorString();
		return;
	}
}

