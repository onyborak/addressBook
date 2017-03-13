#include "addressbookrow.h"


AddressBookRow::AddressBookRow()
{
}

AddressBookRow::AddressBookRow(QDomNode node)
{
	QDomElement element = node.toElement();
	mName = element.attribute("name");
	mSurname = element.attribute("surname");
	mMiddleName = element.attribute("middle_name");
	mSex = element.attribute("sex");
	mPhoneNumber = element.attribute("phone_number");
}

QString AddressBookRow::name() const
{
	return mName;
}

void AddressBookRow::setName(const QString &value)
{
	mName = value;
}

QString AddressBookRow::surname() const
{
	return mSurname;
}

void AddressBookRow::setSurname(const QString &value)
{

	mSurname = value;
}

QString AddressBookRow::middleName() const
{
	return mMiddleName;
}

void AddressBookRow::setMiddleName(const QString &value)
{

	mMiddleName = value;
}

QString AddressBookRow::sex() const
{
	return mSex;
}

void AddressBookRow::setSex(const QString &value)
{
	mSex = value;
}

QString AddressBookRow::phoneNumber() const
{
	return mPhoneNumber;
}

void AddressBookRow::setPhoneNumber(const QString &value)
{
	mPhoneNumber = value;
}

void AddressBookRow::setNode(QDomNode &node)
{
	node.toElement().setAttribute("name", mName);
	node.toElement().setAttribute("surname", mSurname);
	node.toElement().setAttribute("middle_name", mMiddleName);
	node.toElement().setAttribute("sex", mSex);
	node.toElement().setAttribute("phone_number", mPhoneNumber);
}
