#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include "addressbookrow.h"

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
	Q_OBJECT

public:
	explicit EditDialog(QWidget *parent = 0);
	EditDialog(const AddressBookRow &row, QWidget *parent = 0);
	~EditDialog();

	AddressBookRow getRow() const;

private slots:
	void on_name_editingFinished();

	void on_surname_editingFinished();

	void on_middleName_editingFinished();

	void on_phoneNumber_editingFinished();

	void on_male_toggled(bool checked);

	void on_female_toggled(bool checked);

private:
	Ui::EditDialog *ui;
	AddressBookRow mRow;

};

#endif // EDITDIALOG_H
