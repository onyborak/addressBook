#ifndef ONECONNECTION_H
#define ONECONNECTION_H

#include <QObject>
#include <QDataStream>


class QTcpSocket;
class QDomNode;
class QDomDocument;

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

	void sendBook();
	void parseMessage(const QDomDocument &doc);
	void saveBook(const QDomNode &node);
private slots:
	void onReadyRead();

};

#endif // ONECONNECTION_H
