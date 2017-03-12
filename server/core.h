#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QDomNode>
#include <QMutex>

class TcpServer;

class Core : public QObject
{
	Q_OBJECT
public:
	static Core *instance();

	QDomNode book();
	void setBook(const QDomNode &value);

signals:
	void bookChanged(QDomNode book);

public slots:

private:
	Core();
	void saveBook();

	static Core *mSelf;
	QDomNode mBookRoot;
	QMutex mMutex;
	QString mFileName;
};

#endif // CORE_H
