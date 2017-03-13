#ifndef ADDRESSBOOKROW_H
#define ADDRESSBOOKROW_H

#include <QString>
#include <QDomNode>

class AddressBookRow
{
public:
	AddressBookRow(QDomNode node);
	AddressBookRow();

	QString name() const;
	void setName(const QString &value);

	QString surname() const;
	void setSurname(const QString &value);

	QString middleName() const;
	void setMiddleName(const QString &value);

	QString sex() const;
	void setSex(const QString &value);

	QString phoneNumber() const;
	void setPhoneNumber(const QString &value);

	void setNode(QDomNode &node);

private:
	QString mName;
	QString mSurname;
	QString mMiddleName;
	QString mSex;
	QString mPhoneNumber;
};

#endif // ADDRESSBOOKROW_H
