#include "tcpserver.h"

#include "oneconnection.h"

#include <QCoreApplication>
#include <QThread>

TcpServer::TcpServer(QObject *parent)
	: QTcpServer(parent)
{

}

void TcpServer::start()
{
	QStringList args = QCoreApplication::arguments();
	if (args.size() != 1)
	{
		qDebug()<<"Укажите корректные параметры командной строки";
		return;
	}

	bool ok;
	int port = args.first().toInt(&ok);
	if (!ok)
	{
		qDebug()<<"Задан не корректный порт";
		return;
	}
	if (listen(QHostAddress::Any, port))
	{
		qDebug()<<"Сервер успешно запущен";
	}
	else
	{
		qDebug()<<"Ошибка запуска сервера."<<errorString();
	}
}

void TcpServer::incomingConnection(qintptr handle)
{
	OneConnection *connection = new OneConnection(handle);
	QThread *thread = new QThread(this);
	connection->moveToThread(thread);
	connect(thread, &QThread::started, connection, &OneConnection::start);
	connect(connection, &OneConnection::connectingLost, this, [=](){
		thread->quit();
		connection->deleteLater();
	});
	thread->start();
}
