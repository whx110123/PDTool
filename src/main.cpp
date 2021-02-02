#include "frmmain.h"
#include <QApplication>
#include <QTextCodec>
#include <QDesktopWidget>
#include <app.h>
#include "globaldefine.h"
#include "quiwidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setFont(QFont("Microsoft Yahei", 9));

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
	QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
	QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
#else
	QTextCodec *codec = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForLocale(codec);
#endif

	App::Intervals << "1" << "10" << "20" << "50" << "100" << "200" << "300" << "500" << "1000" << "1500" << "2000" << "3000" << "5000" << "10000";
	App::Protocollst << IEC_104 << IEC_101
					 << IEC_103COM << IEC_103WISCOMNET  << IEC_103XUJINET << IEC_103NANZINET << IEC_103BAOXINNET << IEC_103BAOXINNET_NW << IEC_103HUABEI << IEC_103ASDU
					 << MODBUS_RTU << MODBUS_TCP
					 << MEASUREDTERMINAL_NW_NET;
	App::Transferlst << "TCP客户端" << "TCP服务器" << "UDP客户端" << "UDP服务器" << "COM串口";
	App::CRClst << "CRC 16 低位在前" << "CRC 16 高位在前" << "总加和" << "加总异或" ;
	App::Transfermode << "浮点数转四字节" << "四字节转浮点数" << "带符号整数转四字节" << "四字节转带符号整数" << "四字节转无符号整数" << "双精度浮点数转八字节" << "八字节转双精度浮点数";
	App::ConfigFile = QString("%1/%2.ini").arg(QUIHelper::appPath()).arg(QUIHelper::appName());
	App::readConfig();
	App::readSendData();
	App::readDeviceData();

	frmMain w;
	w.setWindowTitle("Protocol Debug Tool V3.01     作者: 王洪星");
	w.show();

	//居中显示窗体
	QDesktopWidget deskWidget;
	int deskWidth = deskWidget.availableGeometry().width();
	int deskHeight = deskWidget.availableGeometry().height();
	QPoint movePoint(deskWidth / 2 - w.width() / 2, deskHeight / 2 - w.height() / 2);
	w.move(movePoint);

	return a.exec();
}
