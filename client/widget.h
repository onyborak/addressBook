#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "bookclient.h"

class AddressBookModel;

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();


private:
	AddressBookModel *mModel;
	BookClient mClient;
	void createGui();

private slots:
	void editRow(const QModelIndex &index);
	void addRow();
};

#endif // WIDGET_H
