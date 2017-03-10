#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
	Q_OBJECT
public:
	TcpServer(QObject *parent = nullptr);
	void start();

protected:
	void incomingConnection( qintptr handle ) override;
};

#endif // TCPSERVER_H
