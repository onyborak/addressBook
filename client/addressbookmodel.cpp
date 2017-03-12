#include "addressbookmodel.h"

#include <QDebug>

AddressBookModel::AddressBookModel(QObject *parent)
	: QAbstractTableModel(parent)
{

}

QVariant AddressBookModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	int row = index.row();
	if (row >= rowCount())
	{
		return QVariant();
	}

	if (role == Qt::DisplayRole)
	{
		switch (index.column())
		{
		case Surname:
			return mRows.at(row).surname();
			break;
		case Name:
			return mRows.at(row).name();
			break;
		case MiddleName:
			return mRows.at(row).middleName();
			break;
		case Sex:
			return mRows.at(row).sex();
			break;
		case Number:
			return mRows.at(row).phoneNumber();
			break;
		}
	}
	return QVariant();
}

QVariant AddressBookModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	static QStringList headers = QStringList()<<"Фамилия"<<"Имя"<<"Отчество"<<"Пол"<<"Номер телефона";
	if (section >= columnCount())
	{
		return QVariant();
	}

	if (orientation == Qt::Horizontal)
	{
		if (role == Qt::DisplayRole)
		{
			return headers.at(section);
		}
	}
	return QAbstractTableModel::headerData(section, orientation, role);
}

int AddressBookModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return Size;
}

int AddressBookModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return mRows.size();
}

bool AddressBookModel::removeRows(int row, int count, const QModelIndex &parent)
{
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), row, row + count - 1);

	while(count > 0 && mRows.size() > row)
	{
		mRows.removeAt(row);
		count--;
	}

	endRemoveRows();
	return true;
}

void AddressBookModel::replaceRow(int row, const AddressBookRow &bookRow)
{
	if (row >= mRows.size())
	{
		return;
	}

	mRows.replace(row, bookRow);
	emit dataChanged(index(row, 0), index(row, columnCount()));
}

QList<AddressBookRow> AddressBookModel::book() const
{
	return mRows;
}

AddressBookRow AddressBookModel::getRow(const QModelIndex &index)
{
	if (index.row() >= rowCount())
	{
		return AddressBookRow();
	}

	return mRows.at(index.row());
}

void AddressBookModel::appendRow(const AddressBookRow &row)
{
	beginInsertRows(QModelIndex(), mRows.size(), mRows.size());
	mRows.append(row);
	endInsertRows();
}

void AddressBookModel::setRows(const QList<AddressBookRow> &rows)
{
	beginResetModel();
	mRows = rows;
	endResetModel();
}
