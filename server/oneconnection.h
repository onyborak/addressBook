#ifndef ONECONNECTION_H
#define ONECONNECTION_H

#include <QObject>
#include <QDataStream>

#include <QDomDocument>


class QTcpSocket;

class OneConnection : public QObject
{
	Q_OBJECT
public:
	OneConnection(quintptr discriptor, QObject *parent = nullptr);

public slots:
	void start();

signals:
	void connectingLost();

private:
	QTcpSocket *mSocket;
	QDataStream mStream;
	static QDomDocument mBook;

	void sendBook();
	void parseMessage(QDomNode &node);
	void saveBook(QDomNode node);
private slots:
	void onReadyRead();

};

#endif // ONECONNECTION_H
