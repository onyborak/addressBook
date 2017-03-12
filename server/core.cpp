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
	if (file.open(QIODevice::ReadOnly))
	{
		QString errorMsg;
		int line, column;
		if (mBook.setContent(&file, &errorMsg, &line, &column))
		{
			qDebug()<<"Файл с книгой успешно подгружен";
		}
		else
		{
			qDebug()<<"Ошибка!"<<errorMsg<<"строчка -"<<line<<"столбец -"<<column;
			mBook = QDomDocument("addressBook");
		}
		file.close();
	}
	else
	{
		mBook = QDomDocument("addressBook");
		qDebug()<<"Не удалось открыть файл:"<<file.fileName()<<file.errorString();
		qDebug()<<"Все хорошо, возможно ее пока никто из клиентов и не создавал, чтобы она тут уже \"лежала\"";
	}
}

void Core::saveBook()
{
	QFile file(mFileName);
	if(file.open(QIODevice::WriteOnly)) {
		if (file.write(mBook.toByteArray()) == -1)
		{
			qDebug()<<"Ошибка записи в файл!"<<file.errorString();
		}
		file.close();
	}
	else
	{
		qDebug()<<"Не удалось открыть файл:"<<file.fileName()<<file.errorString();
	}
}

QDomDocument Core::book()
{
	QMutexLocker locker(&mMutex);
	return mBook;
}

void Core::setBook(const QDomNode &value)
{
	mMutex.lock();
	mBook = QDomDocument("addressBook");
	mBook.appendChild(value);
	saveBook();
	mMutex.unlock();
	emit bookChanged(mBook);
}
