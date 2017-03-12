#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QDomDocument>
#include <QMutex>

class TcpServer;

class Core : public QObject
{
	Q_OBJECT
public:
	static Core *instance();

	QDomDocument book();
	void setBook(const QDomNode &value);

signals:
	void bookChanged(const QDomDocument &book);

public slots:

private:
	Core();
	void saveBook();

	static Core *mSelf;
	QDomDocument mBook;
	QMutex mMutex;
	QString mFileName;
};

#endif // CORE_H
