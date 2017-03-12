#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::EditDialog)
{
	ui->setupUi(this);
	mRow.setSex("Мужской");
}

EditDialog::EditDialog(const AddressBookRow &row, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::EditDialog), mRow(row)
{
	ui->setupUi(this);
	ui->name->setText(row.name());
	ui->surname->setText(row.surname());
	ui->middleName->setText(row.middleName());
	ui->phoneNumber->setText(row.phoneNumber());
	if (row.sex() == "Женский")
	{
		ui->female->setChecked(true);
	}
}

EditDialog::~EditDialog()
{
	delete ui;
}

void EditDialog::on_name_editingFinished()
{
	mRow.setName(ui->name->text());
}

AddressBookRow EditDialog::getRow() const
{
	return mRow;
}

void EditDialog::on_surname_editingFinished()
{
	mRow.setSurname(ui->surname->text());
}

void EditDialog::on_middleName_editingFinished()
{
	mRow.setMiddleName(ui->middleName->text());
}

void EditDialog::on_phoneNumber_editingFinished()
{
	mRow.setPhoneNumber(ui->phoneNumber->text());
}

void EditDialog::on_male_toggled(bool checked)
{
	if (checked)
	{
		mRow.setSex("Мужской");
	}
}

void EditDialog::on_female_toggled(bool checked)
{
	if (checked)
	{
		mRow.setSex("Женский");
	}
}
