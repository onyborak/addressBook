#include "widget.h"
#include "addressbookmodel.h"
#include "configdialog.h"
#include "editdialog.h"
#include <QApplication>
#include <QTableView>

#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>

Widget::Widget(QWidget *parent) :
	QWidget(parent), mClient(this)
{
	mModel = new AddressBookModel(this);
	connect(&mClient, &BookClient::newBook, mModel, &AddressBookModel::setRows);
	connect(&mClient, &BookClient::connectionChanged, this, [=](bool isConnected){
		QString message = isConnected ? "Соединение с сервером установлено" : "Соединение с сервером разорвано";
		QMessageBox::information(this, "", message);
	});
	connect(&mClient, &BookClient::clientError, this, [=](QString error){
		QMessageBox::critical(this, "", error);
	});

	createGui();

	ConfigDialog dlg(this);
	dlg.setModal(true);
	dlg.exec();
	mClient.start(dlg.ip(), dlg.port());
}

void Widget::createGui()
{
	QTableView *table = new QTableView;
	table->setModel(mModel);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(table, &QTableView::doubleClicked, this, &Widget::editRow);

	QPushButton *addButton = new QPushButton("Добавить");
	connect(addButton, &QPushButton::clicked, this, &Widget::addRow);

	QPushButton *removeButton = new QPushButton("Удалить");
	connect(removeButton, &QPushButton::clicked, this, [=](){
		QModelIndex index = table->currentIndex();
		if (index.isValid())
		{
			mModel->removeRows(index.row(), 1, QModelIndex());
			mClient.sendBook(mModel->book());
		}
	});

	QPushButton *editButton = new QPushButton("Изменить");
	connect(editButton, &QPushButton::clicked, this, [=](){
		QModelIndex index = table->currentIndex();
		if (index.isValid())
		{
			editRow(index);
		}
	});

	QHBoxLayout *buttonLay = new QHBoxLayout;
	buttonLay->addStretch();
	buttonLay->addWidget(addButton);
	buttonLay->addWidget(removeButton);
	buttonLay->addWidget(editButton);

	QVBoxLayout *mainLay = new QVBoxLayout(this);
	mainLay->addLayout(buttonLay);
	mainLay->addWidget(table);

	resize(600, 300);
}

void Widget::addRow()
{
	EditDialog dlg(this);
	if (dlg.exec() == QDialog::Accepted)
	{
		mModel->appendRow(dlg.getRow());
		mClient.sendBook(mModel->book());
	}
}

void Widget::editRow(const QModelIndex &index)
{
	AddressBookRow row = mModel->getRow(index);
	EditDialog dlg(row, this);
	if (dlg.exec() == QDialog::Accepted)
	{
		mModel->replaceRow(index.row(), dlg.getRow());
		mClient.sendBook(mModel->book());
	}
}

Widget::~Widget()
{
}

