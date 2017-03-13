#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QObject>
#include <QDomDocument>
#include <QMutex>

class TcpServer;

class AddressBook : public QObject
{
	Q_OBJECT
public:
	static AddressBook *instance();

	QDomDocument book();
	void setBook(const QDomNode &value);

signals:
	void bookChanged(const QDomDocument &book);

public slots:

private:
	AddressBook();
	void saveBook();

	static AddressBook *mSelf;
	QDomDocument mBook;
	QMutex mMutex;
	QString mFileName;
};

#endif // ADDRESSBOOK_H
