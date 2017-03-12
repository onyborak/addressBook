#include "addressbookrow.h"

AddressBookRow::AddressBookRow()
{
	QDomDocument doc("addressBook");
	mNode = doc.createElement("Line");
}

AddressBookRow::AddressBookRow(QDomNode node)
	: mNode(node)
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
	mNode.toElement().setAttribute("name", value);
	mName = value;
}

QString AddressBookRow::surname() const
{
	return mSurname;
}

void AddressBookRow::setSurname(const QString &value)
{
	mNode.toElement().setAttribute("surname", value);
	mSurname = value;
}

QString AddressBookRow::middleName() const
{
	return mMiddleName;
}

void AddressBookRow::setMiddleName(const QString &value)
{
	mNode.toElement().setAttribute("middle_name", value);
	mMiddleName = value;
}

QString AddressBookRow::sex() const
{
	return mSex;
}

void AddressBookRow::setSex(const QString &value)
{
	mNode.toElement().setAttribute("sex", value);
	mSex = value;
}

QString AddressBookRow::phoneNumber() const
{
	return mPhoneNumber;
}

void AddressBookRow::setPhoneNumber(const QString &value)
{
	mNode.toElement().setAttribute("phone_number", value);
	mPhoneNumber = value;
}

QDomNode AddressBookRow::node() const
{
	return mNode;
}
