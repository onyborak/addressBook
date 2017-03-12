#include "configdialog.h"
#include "ui_configdialog.h"

#include <QMessageBox>

ConfigDialog::ConfigDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ConfigDialog)
{
	ui->setupUi(this);
}

ConfigDialog::~ConfigDialog()
{
	delete ui;
}

void ConfigDialog::accept()
{
	mIp = QHostAddress(ui->ip->text());
	if (mIp.isNull())
	{
		QMessageBox::warning(this, "Не правильный ввод данных!", "Введите корректный ip");
		return;
	}

	bool ok;
	mPort = ui->port->text().toInt(&ok);
	if (!ok)
	{
		QMessageBox::warning(this, "Не правильный ввод данных!", "Введите корректный порт");
		return;
	}
	QDialog::accept();
}

int ConfigDialog::port() const
{
	return mPort;
}

QHostAddress ConfigDialog::ip() const
{
	return mIp;
}
