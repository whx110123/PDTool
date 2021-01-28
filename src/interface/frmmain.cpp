//#pragma execution_character_set("utf-8")
#include "frmmain.h"
#include "ui_frmmain.h"
#include "qfile.h"
#include "qtextstream.h"
#include "qtranslator.h"
#include "qdesktopwidget.h"
#include "qdebug.h"
#include "myhighlighter.h"
#include "dialogmodbus.h"

#include <app.h>
#include <iec101.h>
#include <iec103com.h>
#include <iec103netbaoxin.h>
#include <iec103netwiscom.h>
#include <iec104.h>
#include <measuredterminal.h>
#include <modbusrtu.h>
#include <modbustcp.h>
#include <quiwidget.h>

frmMain::frmMain(QWidget *parent) : QMainWindow(parent), ui(new Ui::frmMain)
{
	ui->setupUi(this);
	highlighter1 = new myhighlighter(ui->resulttext->document());
	highlighter2 = new myhighlighter(ui->originaltext->document());
	modbusdlg = new DialogModbus(this);
	this->initForm();
}

frmMain::~frmMain()
{
	delete highlighter1;
	delete highlighter2;
	qDeleteAll(MyBase::mConfig.groups);
	MyBase::mConfig.groups.clear();
	delete ui;
}

void frmMain::initForm()
{
	this->initSignalAndSlots();
	this->initStyle();
	this->initTranslator();
	ui->stackedWidget->setCurrentIndex(0);
	ui->stackedWidget_config->setCurrentIndex(0);

	ui->protocolcbox->addItems(App::Protocollst);
	QStringList list = QStringList();
	list << "1" << "2";
	ui->comboBox_addrlen->addItems(list);
	ui->comboBox_addrlen->addItem("7");
	ui->comboBox_cotlen->addItems(list);
	ui->comboBox_comaddrlen->addItems(list);
	list << "3";
	ui->comboBox_infaddrlen->addItems(list);
	QStringList list1 = QStringList();
	list1 << IEC_SINGLE << IEC_DOUBLESAME << IEC_DOUBLEDIFF;
	ui->comboBox_lengthtype->addItems(list1);
	QStringList list2 = QStringList();
	list2 << YC << YX << YM;
	ui->comboBox1_modbus->addItems(list2);
	ui->comboBox2_modbus->addItems(list2);
	ui->comboBox3_modbus->addItems(list2);
	QStringList list3 = QStringList();
	list3 << SORT1 << SORT2 << SORT3 << SORT4;
	ui->comboBox_sort->addItems(list3);

	ui->comboBox_lengthtype->installEventFilter(this);
	ui->comboBox_addrlen->installEventFilter(this);
	ui->comboBox_cotlen->installEventFilter(this);
	ui->comboBox_comaddrlen->installEventFilter(this);
	ui->comboBox_infaddrlen->installEventFilter(this);
	ui->comboBox_sort->installEventFilter(this);
	ui->comboBox1_modbus->installEventFilter(this);
	ui->comboBox2_modbus->installEventFilter(this);
	ui->comboBox3_modbus->installEventFilter(this);

	ui->protocolcbox->setCurrentIndex(ui->protocolcbox->findText(App::DefaultProtocol));
	ui->stackedWidget_config->setCurrentIndex(0);
	ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
	ui->comboBox_addrlen->setCurrentText("1");
	ui->comboBox_cotlen->setCurrentText("2");
	ui->comboBox_comaddrlen->setCurrentText("2");
	ui->comboBox_infaddrlen->setCurrentText("3");
	highlighter1->hlformat.setForeground(Qt::magenta);
	highlighter1->hlformat.setFontWeight(QFont::Bold);
	highlighter2->hlformat.setForeground(Qt::magenta);
	highlighter2->hlformat.setFontWeight(QFont::Bold);
	on_pushButton_hide_clicked();

	ui->cbcrc->addItems(App::CRClst);
	ui->cbtransform->addItems(App::Transfermode);

}

void frmMain::initSignalAndSlots()
{
	connect(ui->action_Save, &QAction::triggered, this, &frmMain::SaveAll);

	connect(ui->page_debug, &frmDebug::ToTcpClient, ui->page_tcpclient, &frmTcpClient::dealData);
	connect(ui->page_debug, &frmDebug::ToTcpServer, ui->page_tcpserver, &frmTcpServer::dealData);
	connect(ui->page_debug, &frmDebug::ToUdpClient, ui->page_udpclient, &frmUdpClient::dealData);
	connect(ui->page_debug, &frmDebug::ToUdpServer, ui->page_udpserver, &frmUdpServer::dealData);
	connect(ui->page_debug, &frmDebug::ToCom, ui->page_com, &frmComTool::dealData);

	connect(ui->page_tcpclient, &frmTcpClient::TofrmOthers, ui->page_debug, &frmDebug::dealData);
	connect(ui->page_tcpserver, &frmTcpServer::TofrmOthers, ui->page_debug, &frmDebug::dealData);
	connect(ui->page_udpclient, &frmUdpClient::TofrmOthers, ui->page_debug, &frmDebug::dealData);
	connect(ui->page_udpserver, &frmUdpServer::TofrmOthers, ui->page_debug, &frmDebug::dealData);
	connect(ui->page_com, &frmComTool::TofrmOthers, ui->page_debug, &frmDebug::dealData);


	connect(ui->page_iec104master, &frmIEC104Master::ToTcpClient, ui->page_tcpclient, &frmTcpClient::dealData);
	connect(ui->page_iec104master, &frmIEC104Master::ToTcpServer, ui->page_tcpserver, &frmTcpServer::dealData);
	connect(ui->page_iec104master, &frmIEC104Master::ToUdpClient, ui->page_udpclient, &frmUdpClient::dealData);
	connect(ui->page_iec104master, &frmIEC104Master::ToUdpServer, ui->page_udpserver, &frmUdpServer::dealData);
	connect(ui->page_iec104master, &frmIEC104Master::ToCom, ui->page_com, &frmComTool::dealData);

	connect(ui->page_tcpclient, &frmTcpClient::TofrmOthers, ui->page_iec104master, &frmIEC104Master::dealData);
	connect(ui->page_tcpserver, &frmTcpServer::TofrmOthers, ui->page_iec104master, &frmIEC104Master::dealData);
	connect(ui->page_udpclient, &frmUdpClient::TofrmOthers, ui->page_iec104master, &frmIEC104Master::dealData);
	connect(ui->page_udpserver, &frmUdpServer::TofrmOthers, ui->page_iec104master, &frmIEC104Master::dealData);
	connect(ui->page_com, &frmComTool::TofrmOthers, ui->page_iec104master, &frmIEC104Master::dealData);
}

void frmMain::initStyle()
{
	//加载样式表
	QString qss;
	//QFile file(":/qss/psblack.css");
	//QFile file(":/qss/flatwhite.css");
	QFile file(":/qss/lightblue.css");
	if(file.open(QFile::ReadOnly))
	{
#if 1
		//用QTextStream读取样式文件不用区分文件编码 带bom也行
		QStringList list;
		QTextStream in(&file);
		//in.setCodec("utf-8");
		while(!in.atEnd())
		{
			QString line;
			in >> line;
			list << line;
		}

		qss = list.join("\n");
#else
		//用readAll读取默认支持的是ANSI格式,如果不小心用creator打开编辑过了很可能打不开
		qss = QLatin1String(file.readAll());
#endif
		QString paletteColor = qss.mid(20, 7);
		qApp->setPalette(QPalette(QColor(paletteColor)));
		qApp->setStyleSheet(qss);
		file.close();
	}
}

void frmMain::initTranslator()
{
	//加载鼠标右键菜单翻译文件
	QTranslator *translator1 = new QTranslator(qApp);
	translator1->load(":/image/qt_zh_CN.qm");
	qApp->installTranslator(translator1);

	//加载富文本框鼠标右键菜单翻译文件
	QTranslator *translator2 = new QTranslator(qApp);
	translator2->load(":/image/widgets.qm");
	qApp->installTranslator(translator2);
}

void frmMain::SaveAll()
{
	qDebug() << "保存";
}

void frmMain::initProtocolConfig()
{
	MyBase::mConfig.lengthType = ui->comboBox_lengthtype->currentText();
	MyBase::mConfig.addrLen = ui->comboBox_addrlen->currentText().toInt();
	MyBase::mConfig.cotlen = ui->comboBox_cotlen->currentText().toInt();
	MyBase::mConfig.comaddrlen = ui->comboBox_comaddrlen->currentText().toInt();
	MyBase::mConfig.infaddrlen = ui->comboBox_infaddrlen->currentText().toInt();

	qDeleteAll(MyBase::mConfig.groups);
	MyBase::mConfig.groups.clear();
	ModbusDataGroup *datagroup = new ModbusDataGroup;
	datagroup->dataLen = ui->lineEdit1_modbuslen->text().toUInt();
	datagroup->type = ui->comboBox1_modbus->currentText();
	datagroup->analysis = ui->lineEdit1_modbusanalysis->text();
	datagroup->sort = ui->comboBox_sort->currentText();
	MyBase::mConfig.groups.append(datagroup);
	datagroup = new ModbusDataGroup;
	datagroup->dataLen = ui->lineEdit2_modbuslen->text().toUInt();
	datagroup->type = ui->comboBox2_modbus->currentText();
	datagroup->analysis = ui->lineEdit2_modbusanalysis->text();
	datagroup->sort = ui->comboBox_sort->currentText();
	MyBase::mConfig.groups.append(datagroup);
	datagroup = new ModbusDataGroup;
	datagroup->dataLen = ui->lineEdit3_modbuslen->text().toUInt();
	datagroup->type = ui->comboBox3_modbus->currentText();
	datagroup->analysis = ui->lineEdit3_modbusanalysis->text();
	datagroup->sort = ui->comboBox_sort->currentText();
	MyBase::mConfig.groups.append(datagroup);
}



bool frmMain::eventFilter(QObject *obj, QEvent *ev)
{
	if(obj == ui->comboBox_lengthtype ||
			obj == ui->comboBox_addrlen ||
			obj == ui->comboBox_cotlen ||
			obj == ui->comboBox_comaddrlen ||
			obj == ui->comboBox_infaddrlen ||
			obj == ui->comboBox_sort ||
			obj == ui->comboBox1_modbus ||
			obj == ui->comboBox2_modbus ||
			obj == ui->comboBox3_modbus)
	{
		if(ev->type() == QEvent::Wheel)
		{
			return true;
		}
	}
	return QWidget::eventFilter(obj, ev);
}

void frmMain::on_clearBtn_clicked()
{
	ui->originaltext->clear();
	ui->resulttext->clear();
}

void frmMain::on_protocolcbox_currentIndexChanged(const QString& arg1)
{
	if(arg1 == IEC_104)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("2");
		ui->comboBox_comaddrlen->setCurrentText("2");
		ui->comboBox_infaddrlen->setCurrentText("3");
	}
	else if(arg1 == IEC_101)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLESAME);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("2");
	}
	else if(arg1 == IEC_103WISCOMNET)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == IEC_103COM)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLESAME);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == IEC_103ASDU || arg1 == IEC_103NANZINET)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == IEC_103BAOXINNET || arg1 == IEC_103BAOXINNET_NW)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("2");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == IEC_103XUJINET)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("2");
		ui->comboBox_comaddrlen->setCurrentText("2");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == IEC_103HUABEI)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == MODBUS_RTU || arg1 == MODBUS_TCP)
	{
		ui->stackedWidget_config->setCurrentIndex(1);
	}
	else if(arg1 == MEASUREDTERMINAL_NW_NET)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("7");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
}

void frmMain::on_highlightEdit_textChanged(const QString& arg1)
{
	highlighter1->hlstr = arg1;
	highlighter2->hlstr = arg1;
	ui->resulttext->setText(ui->resulttext->toPlainText());
	ui->originaltext->setText(ui->originaltext->toPlainText());
}

void frmMain::on_fontcolor_clicked()
{
	QColor color = QColorDialog::getColor(Qt::magenta, this, tr("颜色对话框"));
	if(color.isValid())
	{
		highlighter1->hlformat.setForeground(color);
		//      highlighter1->hlformat.setFontWeight(QFont::Bold);
		highlighter2->hlformat.setForeground(color);
		//      highlighter2->hlformat.setFontWeight(QFont::Bold);
		ui->resulttext->setText(ui->resulttext->toPlainText());
		ui->originaltext->setText(ui->originaltext->toPlainText());
	}
}

void frmMain::on_backgroundcolor_clicked()
{
	QColor color = QColorDialog::getColor(Qt::white, this, tr("颜色对话框"));
	if(color.isValid())
	{
		highlighter1->hlformat.setBackground(color);
		highlighter2->hlformat.setBackground(color);
		ui->resulttext->setText(ui->resulttext->toPlainText());
		ui->originaltext->setText(ui->originaltext->toPlainText());
	}
}

void frmMain::on_fontchange_clicked()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok, this);
	if(ok)
	{
		highlighter1->hlformat.setFont(font);
		highlighter2->hlformat.setFont(font);
		ui->resulttext->setText(ui->resulttext->toPlainText());
		ui->originaltext->setText(ui->originaltext->toPlainText());
	}
}

void frmMain::on_pushButton_Analysis_clicked()
{
	ui->resulttext->clear();
	App::readConfig();
	QString data = ui->originaltext->toPlainText();
	if(data.length() <= 0)
	{
		return;
	}
	MyBase::mConfig.protocolName = ui->protocolcbox->currentText();

	MyBase *myprotocol = createByName(ui->protocolcbox->currentText());

	if(myprotocol)
	{
		QString tmp;
		int i = 1;
		QByteArray buffer = QUIHelper::hexStrToByteArray(data);
		while(!buffer.isEmpty())
		{
			tmp.append(QString("####第%1帧####\r\n").arg(i++));
			if(myprotocol->init(buffer))
			{
				tmp.append(myprotocol->showToText());
				buffer.remove(0, myprotocol->len);
			}
			else
			{
				if(ui->checkBox_error->isChecked())
				{
					tmp.append(myprotocol->showToText());
				}
				tmp.append(myprotocol->error);
				break;
			}
			tmp.append("****************************************************************************************************\r\n");
		}
		ui->resulttext->setText(tmp);
		delete myprotocol;
		myprotocol = NULL;
	}
}

void frmMain::on_pushButton_change_clicked()
{
	QString data = ui->originaltext->toPlainText();
	if(ui->pushButton_change->text() == "字母大写")
	{
		ui->pushButton_change->setText("字母小写");
		ui->originaltext->setText(data.toUpper());
	}
	else
	{
		ui->pushButton_change->setText("字母大写");
		ui->originaltext->setText(data.toLower());
	}
}

void frmMain::on_pushButton_clean_clicked()
{
	QString data = ui->originaltext->toPlainText();
	QStringList datalist = data.split('\n');
	data.clear();
	for(int i = 0; i < datalist.count(); i++)
	{
		QString tmp = datalist.at(i).trimmed();
		if(tmp.isEmpty())
		{
			continue;
		}
		if((tmp.at(0) >= '0' && tmp.at(0) <= '9') || (tmp.at(0) >= 'a' && tmp.at(0) <= 'f') || (tmp.at(0) >= 'A' && tmp.at(0) <= 'F'))
		{
			tmp.remove("0x");
			data.append(tmp + "\n");
		}

	}
	ui->originaltext->setText(data.trimmed());
}

MyBase *frmMain::createByName(QString name)
{
	initProtocolConfig();

	MyBase *protocol = NULL;
	if(name == IEC_104)           //分析104报文
	{
		protocol = new IEC104;
	}
	else if(name == IEC_101)		//分析101报文
	{
		protocol = new IEC101;
	}
	else if(name == IEC_103WISCOMNET)//分析金智网络103报文
	{
		protocol = new IEC103NetWiscom;
	}
	else if(name == IEC_103COM ||		//分析串口103报文
			name == IEC_103HUABEI)      //分析华北103报文
	{
		protocol = new IEC103COM;
	}
	else if(name == IEC_103BAOXINNET || name == IEC_103BAOXINNET_NW || name == IEC_103XUJINET)
	{
		protocol = new IEC103NetBaoXin;
	}
	else if(name == IEC_103ASDU || name == IEC_103NANZINET)
	{
		protocol = new IEC103Asdu;
	}
	else if(name == MODBUS_RTU)
	{
		protocol = new ModbusRTU;
	}
	else if(name == MODBUS_TCP)
	{
		protocol = new ModbusTCP;
	}
	else if(name == MEASUREDTERMINAL_NW_NET)
	{
		protocol = new MeasuredTerminal;
	}

	return protocol;
}

void frmMain::on_pushButton_hide_clicked()
{
	if(ui->pushButton_hide->text() == "隐藏配置")
	{
		ConfigHide();
	}
	else
	{
		int index = 0;
		if(ui->protocolcbox->currentText() == MODBUS_RTU ||
				ui->protocolcbox->currentText() == MODBUS_TCP)
		{
			index = 1;
		}
		ConfigShow(index);
	}
}

void frmMain::on_pushButton_clicked()
{
	modbusdlg->exec();
}

void frmMain::on_pbcrc_clicked()
{

	QString data = ui->textsource->toPlainText().trimmed();
	QByteArray ba = QUIHelper::hexStrToByteArray(data);
	uchar crcarray[2] = {0};
	int crclen = 0;
	if(ui->cbcrc->currentText().contains("CRC 16 低位在前"))
	{
		crclen = 2;
		ushort crc = crc16((uchar *)ba.data(), ba.length());
		crcarray[0] = crc & 0xff;
		crcarray[1] = (crc >> 8) & 0xff;
	}
	else if(ui->cbcrc->currentText().contains("CRC 16 高位在前"))
	{
		crclen = 2;
		ushort crc = crc16((uchar *)ba.data(), ba.length());
		crcarray[1] = crc & 0xff;
		crcarray[0] = (crc >> 8) & 0xff;
	}
	else if(ui->cbcrc->currentText().contains("总加和"))
	{
		crclen = 1;
		for(int i = 0; i < ba.length(); i++)
		{
			crcarray[0] += *(uchar *)(ba.data() + i);
		}
	}
	else if(ui->cbcrc->currentText().contains("加总异或"))
	{
		crclen = 1;
		for(int i = 0; i < ba.length(); i++)
		{
			crcarray[0] ^= *(uchar *)(ba.data() + i);
		}
	}


	for(int i = 0; i < crclen; i++)
	{
		data.append(" " + CharToHexStr(crcarray[i]));
	}
	ui->textdestination->setText(data.toUpper());
}

void frmMain::on_pbtransform_clicked()
{
	QString data = ui->linesource->text().trimmed();
	QString dataout;
	float datafloat = 0;
	double datadouble = 0;
	uint datauint = 0;
	int dataint = 0;
	if(ui->cbtransform->currentText().contains("浮点数转四字节"))
	{
		datafloat = data.toFloat();
		QByteArray ba((char *)&datafloat, 4);
		if(!ui->checkreverse->isChecked())
		{
			BaReverse(ba);
		}
		dataout.append(CharToHexStr(ba.data(), 4));
	}
	else if(ui->cbtransform->currentText().contains("四字节转浮点数"))
	{
		QByteArray ba = QUIHelper::hexStrToByteArray(data);
		if(ba.length() == 4)
		{
			int model = 1;
			if(ui->checkreverse->isChecked())
			{
				model = 0;
			}
			datafloat = charTofloat((uchar *)ba.data(), model);
			dataout = QString::number(datafloat, 'g', 10);
		}
	}
	else if(ui->cbtransform->currentText().contains("带符号整数转四字节"))
	{
		dataint = data.toInt();
		QByteArray ba((char *)&dataint, 4);
		if(!ui->checkreverse->isChecked())
		{
			BaReverse(ba);
		}
		dataout.append(CharToHexStr(ba.data(), 4));

	}
	else if(ui->cbtransform->currentText().contains("四字节转带符号整数"))
	{
		QByteArray ba = QUIHelper::hexStrToByteArray(data);
		if(ba.length() == 4)
		{
			int model = 1;
			if(ui->checkreverse->isChecked())
			{
				model = 0;
			}
			dataint = charToint((uchar *)ba.data(), 4, model);
			dataout = QString::number(dataint);
		}
	}
	else if(ui->cbtransform->currentText().contains("四字节转无符号整数"))
	{
		QByteArray ba = QUIHelper::hexStrToByteArray(data);
		if(ba.length() == 4)
		{
			int model = 1;
			if(ui->checkreverse->isChecked())
			{
				model = 0;
			}
			datauint = charTouint((uchar *)ba.data(), 4, model);
			dataout = QString::number(datauint);
		}
	}
	if(ui->cbtransform->currentText().contains("双精度浮点数转八字节"))
	{
		datadouble = data.toDouble();
		QByteArray ba((char *)&datadouble, 8);
		if(!ui->checkreverse->isChecked())
		{
			BaReverse(ba);
		}
		dataout.append(CharToHexStr(ba.data(), 8));

	}
	else if(ui->cbtransform->currentText().contains("八字节转双精度浮点数"))
	{
		QByteArray ba = QUIHelper::hexStrToByteArray(data);
		if(ba.length() == 8)
		{
			if(!ui->checkreverse->isChecked())
			{
				BaReverse(ba);
			}
			dataout = QString::number(*(double *)ba.data(), 'g', 20);
		}
	}
	ui->linedestination->setText(dataout.trimmed());

}

void frmMain::on_Bt1_clicked()
{
	QString text = ui->Le1->toPlainText();
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
	QString tmpgbk;
	QString tmputf8;
	QString tmpunicode;
	QByteArray hex_data;
	for(QChar byte : text)
	{
		tmpgbk.append(gbk->fromUnicode(byte).toHex() + " ");
		tmputf8.append(utf8->fromUnicode(byte).toHex() + " ");
		tmpunicode.append(QString::number(byte.unicode(), 16) + " ");
	}
	ui->Le2->setText(tmpgbk.trimmed().toUpper());
	ui->Le3->setText(tmputf8.trimmed().toUpper());
	ui->Le4->setText(tmpunicode.trimmed().toUpper());
}

void frmMain::on_Bt2_clicked()
{
	QString tmp;
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
	QString tmpgbk;
	QString tmputf8;
	QString tmpunicode;
	QByteArray ba = QUIHelper::hexStrToByteArray(ui->Le2->text());
	tmp = gbk->toUnicode(ba);
	for(QChar byte : tmp)
	{
		tmputf8.append(utf8->fromUnicode(byte).toHex() + " ");
		tmpunicode.append(QString::number(byte.unicode(), 16) + " ");
	}

	ui->Le1->setPlainText(tmp);
	ui->Le3->setText(tmputf8.trimmed().toUpper());
	ui->Le4->setText(tmpunicode.trimmed().toUpper());
}

void frmMain::on_Bt3_clicked()
{
	QString tmp;
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
	QString tmpgbk;
	QString tmputf8;
	QString tmpunicode;
	QByteArray ba = QUIHelper::hexStrToByteArray(ui->Le3->text());
	tmp = utf8->toUnicode(ba);
	for(QChar byte : tmp)
	{
		tmpgbk.append(gbk->fromUnicode(byte).toHex() + " ");
		tmpunicode.append(QString::number(byte.unicode(), 16) + " ");
	}

	ui->Le1->setPlainText(tmp);
	ui->Le2->setText(tmpgbk.trimmed().toUpper());
	ui->Le4->setText(tmpunicode.trimmed().toUpper());
}

void frmMain::on_Bt4_clicked()
{
	QString tmp;
	QStringList strlst = ui->Le4->text().split(" ");
	strlst.removeAll("");
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
	QString tmpgbk;
	QString tmputf8;
	for(QString str : strlst)
	{
		QChar byte(str.toUInt(0, 16));
		tmp.append(byte);
		tmpgbk.append(gbk->fromUnicode(byte).toHex() + " ");
		tmputf8.append(utf8->fromUnicode(byte).toHex() + " ");
	}

	ui->Le1->setPlainText(tmp);
	ui->Le2->setText(tmpgbk.trimmed().toUpper());
	ui->Le3->setText(tmputf8.trimmed().toUpper());
}

void frmMain::on_Bt_clear_clicked()
{
	ui->Le1->clear();
	ui->Le2->clear();
	ui->Le3->clear();
	ui->Le4->clear();
	ui->textsource->clear();
	ui->textdestination->clear();
	ui->linesource->clear();
	ui->linedestination->clear();
}



void frmMain::on_action_TCPClient_triggered()
{
	ui->stackedWidget->setCurrentIndex(1);
	setWindowTitle("TCP客户端    Protocol Debug Tool V3.00     作者: 王洪星");
}

void frmMain::on_action_TCPServer_triggered()
{
	ui->stackedWidget->setCurrentIndex(2);
	setWindowTitle("TCP服务端    Protocol Debug Tool V3.00     作者: 王洪星");
}

void frmMain::on_action_UDPClient_triggered()
{
	ui->stackedWidget->setCurrentIndex(3);
	setWindowTitle("UDP客户端    Protocol Debug Tool V3.00     作者: 王洪星");
}

void frmMain::on_action_UDPServer_triggered()
{
	ui->stackedWidget->setCurrentIndex(4);
	setWindowTitle("UDP服务端    Protocol Debug Tool V3.00     作者: 王洪星");
}

void frmMain::on_action_COM_triggered()
{
	ui->stackedWidget->setCurrentIndex(5);
	setWindowTitle("COM串口    Protocol Debug Tool V3.00     作者: 王洪星");
}

void frmMain::on_action_Analys_triggered()
{
	ui->stackedWidget->setCurrentIndex(0);
	setWindowTitle("报文解析    Protocol Debug Tool V3.00     作者: 王洪星");
}

void frmMain::ConfigHide()
{
	ui->pushButton_hide->setText("打开配置");
	ui->stackedWidget_config->hide();

	ui->action_HandleData->setChecked(false);
	ui->action_SendData->setChecked(false);
	ui->action_IEC104Master->setChecked(false);
}

void frmMain::ConfigShow(int index)
{
	ui->pushButton_hide->setText("隐藏配置");
	ui->stackedWidget_config->setCurrentIndex(index);
	if(ui->stackedWidget_config->isHidden())
	{
		ui->stackedWidget_config->show();
	}
}

void frmMain::on_action_HandleData_triggered(bool checked)
{
	ConfigHide();
	if(checked == true)
	{
		ui->action_HandleData->setChecked(true);
		ConfigShow(2);
	}
}

void frmMain::on_action_SendData_triggered(bool checked)
{
	ConfigHide();
	if(checked == true)
	{
		ui->action_SendData->setChecked(true);
		ConfigShow(3);
	}
}

void frmMain::on_action_IEC104Master_triggered(bool checked)
{
	ConfigHide();
	if(checked == true)
	{
		ui->action_IEC104Master->setChecked(true);
		ConfigShow(4);
	}
}
