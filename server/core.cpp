#include "core.h"
#include <QFile>
#include <QCoreApplication>
#include <QDebug>

Core *Core::mSelf = 0;

Core *Core::instance()
{
	if (!mSelf)
	{
		mSelf = new Core;
	}
	return mSelf;
}

Core::Core()
{
	mFileName = QCoreApplication::applicationDirPath() + "/addressBook.xml";
	QFile file(mFileName);
	QDomDocument book;
	if (file.open(QIODevice::ReadOnly))
	{
		QString errorMsg;
		int line, column;
		if (book.setContent(&file, &errorMsg, &line, &column))
		{
			qDebug()<<"Файл с книгой успешно подгружен";
			mBookRoot = book.firstChild();
		}
		else
		{
			qDebug()<<"Ошибка!"<<errorMsg<<"строчка -"<<line<<"столбец -"<<column;
		}
		file.close();
	}
	else
	{
		qDebug()<<"Не удалось открыть файл:"<<file.fileName()<<file.errorString();
		qDebug()<<"Все хорошо, возможно ее пока никто из клиентов и не создавал, чтобы она тут уже \"лежала\"";
	}
}

void Core::saveBook()
{
	QFile file(mFileName);
	if(file.open(QIODevice::WriteOnly)) {
		if (file.write(mBookRoot.toDocument().toByteArray()) == -1)
		{
			qDebug()<<"Ошибка записи в файл!"<<file.errorString();
		}
		else
		{
			qDebug()<<"Файл успешно записан!";
		}
		file.close();
	}
	else
	{
		qDebug()<<"Не удалось открыть файл:"<<file.fileName()<<file.errorString();
	}
}

QDomNode Core::book()
{
	QMutexLocker locker(&mMutex);
	return mBookRoot;
}

void Core::setBook(const QDomNode &value)
{
	if (value == mBookRoot)
		return;

	mMutex.lock();
	mBookRoot = value;
	saveBook();
	mMutex.unlock();
	emit bookChanged(mBookRoot);
}
