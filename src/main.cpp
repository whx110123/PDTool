#include "mainwindow.h"

#include <QApplication>
#include <app.h>
#include <quiwidget.h>
#include "globaldefine.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QFont font;
	font.setFamily(QUIConfig::FontName);
	font.setPixelSize(QUIConfig::FontSize);
	a.setFont(font);

	//设置编码以及加载中文翻译文件
	QUIHelper::setCode();
	QUIHelper::setTranslator(":/res/qt_zh_CN.qm");
	QUIHelper::setTranslator(":/res/widgets.qm");
	QUIHelper::initRand();

	App::Intervals << "1" << "10" << "20" << "50" << "100" << "200" << "300" << "500" << "1000" << "1500" << "2000" << "3000" << "5000" << "10000";
	App::Protocollst << IEC_104 << IEC_101
					 << IEC_103COM << IEC_103WISCOMNET  << IEC_103XUJINET << IEC_103NANZINET << IEC_103BAOXINNET << IEC_103HUABEI << IEC_103ASDU
					 << MODBUS_RTU << MODBUS_TCP
					 << MEASUREDTERMINAL_NW_NET;
	App::Transferlst << "TCP客户端" << "TCP服务器" << "UDP客户端" << "UDP服务器" << "COM串口";
	App::CRClst << "CRC 16 低位在前" << "CRC 16 高位在前" << "总加和" << "加总异或" ;
	App::Transfermode << "浮点数转四字节" << "四字节转浮点数" << "带符号整数转四字节" << "四字节转带符号整数" << "四字节转无符号整数" << "双精度浮点数转八字节" << "八字节转双精度浮点数";
	App::ConfigFile = QString("%1/%2.ini").arg(QUIHelper::appPath()).arg(QUIHelper::appName());
	App::readConfig();
	App::readSendData();
	App::readDeviceData();
	MainWindow w;
	w.setWindowTitle(QString("规约调试工具V3.00   ") + QString("作者：王洪星") + QString("  本机IP: %1 ").arg(QUIHelper::getLocalIP()));
	w.show();
//	w.changeImage();
	return a.exec();
}
