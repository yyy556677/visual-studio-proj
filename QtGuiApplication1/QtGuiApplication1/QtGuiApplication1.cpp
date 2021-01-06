#include "QtGuiApplication1.h"
#include <QtNetwork/qudpsocket.h>
#include <qdebug.h>

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QUdpSocket u;
	if (false == u.bind(QHostAddress("192.168.0.102"), 50001))
	{
		qDebug() << "bind error";
	}
	qDebug() << "bind success";
}
