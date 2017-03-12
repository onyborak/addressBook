#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
	Q_OBJECT
public:
	TcpServer(QObject *parent = nullptr);
	bool start();

protected:
	void incomingConnection( qintptr handle ) Q_DECL_OVERRIDE;
};

#endif // TCPSERVER_H
