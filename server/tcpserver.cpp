#include "tcpserver.h"

#include "oneconnection.h"

#include <QCoreApplication>
#include <QThread>
#include <iostream>

TcpServer::TcpServer(QObject *parent)
	: QTcpServer(parent)
{

}

bool TcpServer::start()
{
	int port;
	qDebug()<<"Введите порт сервера";
	std::cin >> port;
	if (listen(QHostAddress::Any, port))
	{
		qDebug()<<"Сервер успешно запущен";
		return true;
	}

	qDebug()<<"Ошибка запуска сервера."<<errorString();
	return false;
}

void TcpServer::incomingConnection(qintptr handle)
{
	OneConnection *connection = new OneConnection(handle);
	QThread *thread = new QThread(this);
	connection->moveToThread(thread);
	connect(thread, &QThread::started, connection, &OneConnection::start);
	connect(connection, &OneConnection::connectingLost, this, [=](){
		qDebug()<<"Клиент отключился. Удаляем...";
		thread->quit();
		connection->deleteLater();
	});
	connect(thread, &QThread::finished, this, [=](){
		delete thread;
		qDebug()<<"Удалили";
	});
	thread->start();
}
