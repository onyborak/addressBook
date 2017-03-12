#ifndef BOOKCLIENT_H
#define BOOKCLIENT_H
#include "addressbookrow.h"

#include <QObject>
#include <QDataStream>
#include <QTcpSocket>

class QHostAddress;

class BookClient : public QObject
{
	Q_OBJECT
public:
	explicit BookClient(QObject *parent = 0);

	void start(const QHostAddress &serverAddress, int serverPort);

public slots:
	void sendBook(const QList<AddressBookRow> &book);

signals:
	void newBook(QList<AddressBookRow> book);
	void clientError(QString errorMsg);
	void connectionChanged(bool isConnected);

private:
	QTcpSocket *mSocket;
	QDataStream mStream;

	void requestBook();
private slots:
	void onReadyRead();

};

#endif // BOOKCLIENT_H
