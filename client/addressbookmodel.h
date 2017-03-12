#ifndef ADDRESSBOOKMODEL_H
#define ADDRESSBOOKMODEL_H

#include <QAbstractTableModel>
#include <addressbookrow.h>

class AddressBookModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	AddressBookModel(QObject *parent = 0);

	QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	bool removeRows(int row, int count, const QModelIndex &parent) Q_DECL_OVERRIDE;

	void appendRow(const AddressBookRow &row);
	void replaceRow(int row, const AddressBookRow &bookRow);
	QList<AddressBookRow> book() const;
	AddressBookRow getRow(const QModelIndex &index);

public slots:
	void setRows(const QList<AddressBookRow> &rows);

private:
	enum Columns
	{
		Surname,
		Name,
		MiddleName,
		Sex,
		Number,
		Size
	};
	QList<AddressBookRow> mRows;

};

#endif // ADDRESSBOOKMODEL_H
