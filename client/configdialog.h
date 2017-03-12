#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QHostAddress>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ConfigDialog(QWidget *parent = 0);
	~ConfigDialog();

	QHostAddress ip() const;
	int port() const;

public slots:
	void accept() Q_DECL_OVERRIDE;

private:
	Ui::ConfigDialog *ui;
	QHostAddress mIp;
	int mPort;
};

#endif // CONFIGDIALOG_H
