#include <QCoreApplication>
#include <QTextCodec>

#include "tcpserver.h"
#include "addressbook.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

#ifdef Q_OS_WIN32
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
#endif
#ifdef Q_OS_LINUX
		QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

	AddressBook::instance();
	TcpServer server;
	server.start();
	
	return a.exec();
}
