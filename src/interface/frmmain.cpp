//#pragma execution_character_set("utf-8")
#include "frmmain.h"
#include "ui_frmmain.h"
#include "myhighlighter.h"
#include "dlgmodbus.h"
#include "dlgintroduction.h"
#include "dlgchangelog.h"

#include <app.h>
#include <iec101.h>
#include <iec103com.h>
#include <iec103netbaoxin.h>
#include <iec103netwiscom.h>
#include <iec104.h>
#include <iec61850.h>
#include <measuredterminal.h>
#include <modbusrtu.h>
#include <modbustcp.h>
#include <quiwidget.h>

frmMain::frmMain(QWidget *parent) : QMainWindow(parent), ui(new Ui::frmMain)
{
	ui->setupUi(this);
	highlighter1 = new myhighlighter(ui->resulttext->document());
	highlighter2 = new myhighlighter(ui->originaltext->document());
	modbusdlg = new DlgModbus(this);
	this->initForm();
}

frmMain::~frmMain()
{
	delete highlighter1;
	delete highlighter2;

	delete ui;
}

void frmMain::initForm()
{
	this->initSignalAndSlots();
	this->initStyle();
	this->initTranslator();
	ui->stackedWidget->setCurrentIndex(0);
	ui->stackedWidget_config->setCurrentIndex(0);
	ui->splitter->setStretchFactor(0, 2);
	ui->splitter->setStretchFactor(1, 1);
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
	list1 << IEC_SINGLE << IEC_DOUBLESAME << IEC_DOUBLEDIFF << IEC_FOURDIFF;
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
	on_protocolcbox_currentIndexChanged(App::DefaultProtocol);

	highlighter1->hlformat.setForeground(Qt::magenta);
	highlighter1->hlformat.setFontWeight(QFont::Bold);
	highlighter2->hlformat.setForeground(Qt::magenta);
	highlighter2->hlformat.setFontWeight(QFont::Bold);
	on_pushButton_hide_clicked();

	popMenu_Analysis = new QMenu(this);
	clearSeeds_Analysis = new QAction(tr("清空列表"), this);
	popMenu_Analysis->addAction(clearSeeds_Analysis);
	connect(clearSeeds_Analysis, &QAction::triggered, this, &frmMain::clearlist);

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

	connect(ui->page_tcpclient, &frmTcpClient::TofrmOthers, ui->page_iec104master, &frmIEC104Master::dealRcvData);
	connect(ui->page_tcpserver, &frmTcpServer::TofrmOthers, ui->page_iec104master, &frmIEC104Master::dealRcvData);
	connect(ui->page_udpclient, &frmUdpClient::TofrmOthers, ui->page_iec104master, &frmIEC104Master::dealRcvData);
	connect(ui->page_udpserver, &frmUdpServer::TofrmOthers, ui->page_iec104master, &frmIEC104Master::dealRcvData);
	connect(ui->page_com, &frmComTool::TofrmOthers, ui->page_iec104master, &frmIEC104Master::dealRcvData);

	connect(ui->page_MTMaster, &frmMeasuredTerminalMaster::ToTcpClient, ui->page_tcpclient, &frmTcpClient::dealData);
	connect(ui->page_MTMaster, &frmMeasuredTerminalMaster::ToTcpServer, ui->page_tcpserver, &frmTcpServer::dealData);
	connect(ui->page_MTMaster, &frmMeasuredTerminalMaster::ToUdpClient, ui->page_udpclient, &frmUdpClient::dealData);
	connect(ui->page_MTMaster, &frmMeasuredTerminalMaster::ToUdpServer, ui->page_udpserver, &frmUdpServer::dealData);
	connect(ui->page_MTMaster, &frmMeasuredTerminalMaster::ToCom, ui->page_com, &frmComTool::dealData);

	connect(ui->page_tcpclient, &frmTcpClient::TofrmOthers, ui->page_MTMaster, &frmMeasuredTerminalMaster::dealRcvData);
	connect(ui->page_tcpserver, &frmTcpServer::TofrmOthers, ui->page_MTMaster, &frmMeasuredTerminalMaster::dealRcvData);
	connect(ui->page_udpclient, &frmUdpClient::TofrmOthers, ui->page_MTMaster, &frmMeasuredTerminalMaster::dealRcvData);
	connect(ui->page_udpserver, &frmUdpServer::TofrmOthers, ui->page_MTMaster, &frmMeasuredTerminalMaster::dealRcvData);
	connect(ui->page_com, &frmComTool::TofrmOthers, ui->page_MTMaster, &frmMeasuredTerminalMaster::dealRcvData);

	connect(ui->page_iec104master, &frmIEC104Master::toLog, ui->page_log, &frmLog::handleLog);
	connect(ui->page_MTMaster, &frmMeasuredTerminalMaster::toLog, ui->page_log, &frmLog::handleLog);
}

void frmMain::initStyle()
{
	switch(App::CurrentSkin)
	{
	case 0:
		on_action_lightblue_triggered();
		break;
	case 1:
		on_action_flatwhite_triggered();
		break;
	case 2:
		on_action_psblack_triggered();
		break;
	case 3:
		on_action_wiscom_triggered();
		break;
	default:
		break;
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

MyConfig frmMain::initProtocolConfig()
{
	MyConfig Config;
	Config.protocolName = ui->protocolcbox->currentText();
	Config.lengthType = ui->comboBox_lengthtype->currentText();
	Config.addrLen = ui->comboBox_addrlen->currentText().toInt();
	Config.cotlen = ui->comboBox_cotlen->currentText().toInt();
	Config.comaddrlen = ui->comboBox_comaddrlen->currentText().toInt();
	Config.infaddrlen = ui->comboBox_infaddrlen->currentText().toInt();

	Config.groups.clear();
	ModbusDataGroup datagroup;
	datagroup.dataLen = ui->lineEdit1_modbuslen->text().toUInt();
	datagroup.type = ui->comboBox1_modbus->currentText();
	datagroup.analysis = ui->lineEdit1_modbusanalysis->text();
	datagroup.sort = ui->comboBox_sort->currentText();
	Config.groups.append(datagroup);

	datagroup.dataLen = ui->lineEdit2_modbuslen->text().toUInt();
	datagroup.type = ui->comboBox2_modbus->currentText();
	datagroup.analysis = ui->lineEdit2_modbusanalysis->text();
	datagroup.sort = ui->comboBox_sort->currentText();
	Config.groups.append(datagroup);

	datagroup.dataLen = ui->lineEdit3_modbuslen->text().toUInt();
	datagroup.type = ui->comboBox3_modbus->currentText();
	datagroup.analysis = ui->lineEdit3_modbusanalysis->text();
	datagroup.sort = ui->comboBox_sort->currentText();
	Config.groups.append(datagroup);
	return Config;
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
	ActionHide();
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
		ui->comboBox_lengthtype->setCurrentText(IEC_FOURDIFF);
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
//	ui->resulttext->setText(ui->resulttext->toPlainText());
	initcursor();
//	on_pushButton_after_clicked();
//	ui->originaltext->setText(ui->originaltext->toPlainText());
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
		ui->resulttext->setPlainText(ui->resulttext->toPlainText());
		initcursor();
		ui->originaltext->setPlainText(ui->originaltext->toPlainText());
	}
}

void frmMain::on_backgroundcolor_clicked()
{
	QColor color = QColorDialog::getColor(Qt::white, this, tr("颜色对话框"));
	if(color.isValid())
	{
		highlighter1->hlformat.setBackground(color);
		highlighter2->hlformat.setBackground(color);
		ui->resulttext->setPlainText(ui->resulttext->toPlainText());
		initcursor();
		ui->originaltext->setPlainText(ui->originaltext->toPlainText());
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
		ui->resulttext->setPlainText(ui->resulttext->toPlainText());
		initcursor();
		ui->originaltext->setPlainText(ui->originaltext->toPlainText());
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
	QByteArray buffer = QUIHelper::hexStrToByteArray(data);
	if(buffer.length() <= 0)
	{
		return;
	}
	MyBase *myprotocol = createByName(ui->protocolcbox->currentText());

	if(myprotocol)
	{
		//总解析
		QString tmp;
		//单帧解析
		QString tmpOne;
		int i = 0;
		QTreeWidgetItem *headItem = new QTreeWidgetItem(ui->treeWidget_Analysis, QTreeWidgetItem::UserType);
		ui->treeWidget_Analysis->setCurrentItem(headItem);
		headItem->setText(0, QString("全部") + QString::number(ui->treeWidget_Analysis->topLevelItemCount()));
		//设置禁止展开
		ui->treeWidget_Analysis->setItemsExpandable(false);
		//当前进度
		int progressValue = 0;
		ui->progressBar_Analysis->setMaximum(buffer.length());

		while(!buffer.isEmpty())
		{
			tmpOne.clear();
			tmpOne.append(QString("####第%1帧####\r\n").arg(++i));
			if(myprotocol->init(buffer))
			{
				tmpOne.append(myprotocol->showToText());
				buffer.remove(0, myprotocol->mLen);
				tmpOne.append("****************************************************************************************************\r\n");
				progressValue += myprotocol->mLen;
				ui->progressBar_Analysis->setValue(progressValue);
				QApplication::processEvents();
			}
			else
			{
				if(ui->checkBox_error->isChecked())
				{
					tmpOne.append(myprotocol->showToText());
				}
				tmpOne.append(myprotocol->mError);
				buffer.clear();
			}
			QTreeWidgetItem *item = new QTreeWidgetItem(headItem, QTreeWidgetItem::UserType + i);
			item->setText(0, QString::number(i));
			item->setData(0, Qt::UserRole, tmpOne);
			tmp.append(tmpOne);
		}
		headItem->setData(0, Qt::UserRole, tmp);
		ui->resulttext->setPlainText(tmp);
		initcursor();
		ui->progressBar_Analysis->setValue(0);
		ui->treeWidget_Analysis->setItemsExpandable(true);

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
		ui->originaltext->setPlainText(data.toUpper());
	}
	else
	{
		ui->pushButton_change->setText("字母大写");
		ui->originaltext->setPlainText(data.toLower());
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
	ui->originaltext->setPlainText(data.trimmed());
}

MyBase *frmMain::createByName(QString name)
{
	MyConfig Config = initProtocolConfig();


	MyBase *protocol = NULL;
	if(name == IEC_104)           //分析104报文
	{
		protocol = new IEC104(Config);
	}
	else if(name == IEC_101)		//分析101报文
	{
		protocol = new IEC101(Config);
	}
	else if(name == IEC_103WISCOMNET)//分析金智网络103报文
	{
		protocol = new IEC103NetWiscom(Config);
	}
	else if(name == IEC_103COM ||		//分析串口103报文
			name == IEC_103HUABEI)      //分析华北103报文
	{
		protocol = new IEC103COM(Config);
	}
	else if(name == IEC_103BAOXINNET || name == IEC_103BAOXINNET_NW || name == IEC_103XUJINET)
	{
		protocol = new IEC103NetBaoXin(Config);
	}
	else if(name == IEC_103ASDU || name == IEC_103NANZINET)
	{
		protocol = new IEC103Asdu(Config);
	}
	else if(name == MODBUS_RTU)
	{
		protocol = new ModbusRTU(Config);
	}
	else if(name == MODBUS_TCP)
	{
		protocol = new ModbusTCP(Config);
	}
	else if(name == MEASUREDTERMINAL_NW_NET)
	{
		protocol = new MeasuredTerminal(Config);
	}
	else if(name == IEC_61850)
	{
		protocol = new IEC61850(Config);
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


void frmMain::on_action_TCPClient_triggered()
{
	ui->stackedWidget->setCurrentIndex(1);
	setWindowTitle("TCP客户端    " + APPTITLE);
}

void frmMain::on_action_TCPServer_triggered()
{
	ui->stackedWidget->setCurrentIndex(2);
	setWindowTitle("TCP服务端    " + APPTITLE);
}

void frmMain::on_action_UDPClient_triggered()
{
	ui->stackedWidget->setCurrentIndex(3);
	setWindowTitle("UDP客户端    " + APPTITLE);
}

void frmMain::on_action_UDPServer_triggered()
{
	ui->stackedWidget->setCurrentIndex(4);
	setWindowTitle("UDP服务端    " + APPTITLE);
}

void frmMain::on_action_COM_triggered()
{
	ui->stackedWidget->setCurrentIndex(5);
	setWindowTitle("COM串口    " + APPTITLE);
}

void frmMain::on_action_Analys_triggered()
{
	ui->stackedWidget->setCurrentIndex(0);
	setWindowTitle("报文解析    " + APPTITLE);
}

void frmMain::on_action_Log_triggered()
{
	ui->stackedWidget->setCurrentIndex(6);
	setWindowTitle("日志系统    " + APPTITLE);
}
void frmMain::ConfigHide()
{
	ui->pushButton_hide->setText("打开配置");
	ui->stackedWidget_config->hide();
	ActionHide();

}

void frmMain::ActionHide()
{
	ui->action_HandleData->setChecked(false);
	ui->action_SendData->setChecked(false);
	ui->action_IEC104Master->setChecked(false);
	ui->action_MeasuredTerminalMaster->setChecked(false);
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

void frmMain::initcursor()
{
	currentIndex = 0;
	ui->resulttext->moveCursor(QTextCursor::Start);
	tc = ui->resulttext->textCursor();
	ui->pushButton_before->setToolTip(QString());
	ui->pushButton_after->setToolTip(QString());
}

void frmMain::clearlist()
{
	if(ui->treeWidget_Analysis->topLevelItemCount() > 0)
	{
		ui->treeWidget_Analysis->reset();
		ui->treeWidget_Analysis->clear();
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

void frmMain::on_action_MeasuredTerminalMaster_triggered(bool checked)
{
	ConfigHide();
	if(checked == true)
	{
		ui->action_MeasuredTerminalMaster->setChecked(true);
		ConfigShow(5);
	}
}

void frmMain::on_action_lightblue_triggered()
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
	App::CurrentSkin = 0;
	App::writeConfig();
}

void frmMain::on_action_flatwhite_triggered()
{
	//加载样式表
	QString qss;
	//QFile file(":/qss/psblack.css");
	QFile file(":/qss/flatwhite.css");
	//QFile file(":/qss/lightblue.css");
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
	App::CurrentSkin = 1;
	App::writeConfig();
}

void frmMain::on_action_psblack_triggered()
{
	//加载样式表
	QString qss;
	QFile file(":/qss/psblack.css");
	//QFile file(":/qss/flatwhite.css");
	//QFile file(":/qss/lightblue.css");
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
	App::CurrentSkin = 2;
	App::writeConfig();
}

void frmMain::on_action_Update_triggered()
{
	DlgChangeLog dlg;
	dlg.exec();
}

void frmMain::on_action_Exit_triggered()
{
	qApp->closeAllWindows();
}

void frmMain::on_pushButton_before_clicked()
{
	ui->resulttext->setTextCursor(tc);
	if(ui->resulttext->find(ui->highlightEdit->text(), QTextDocument::FindBackward))
	{
		tc = ui->resulttext->textCursor();
		currentIndex--;
	}
	auto sum = ui->resulttext->toPlainText().count(ui->highlightEdit->text(), Qt::CaseInsensitive);
	ui->pushButton_before->setToolTip(QString("%1/%2").arg(currentIndex).arg(sum));
	ui->pushButton_after->setToolTip(QString("%1/%2").arg(currentIndex).arg(sum));
}

void frmMain::on_pushButton_after_clicked()
{
	ui->resulttext->setTextCursor(tc);
	if(ui->resulttext->find(ui->highlightEdit->text()))
	{
		tc = ui->resulttext->textCursor();
		currentIndex++;
	}
	auto sum = ui->resulttext->toPlainText().count(ui->highlightEdit->text(), Qt::CaseInsensitive);
	ui->pushButton_before->setToolTip(QString("%1/%2").arg(currentIndex).arg(sum));
	ui->pushButton_after->setToolTip(QString("%1/%2").arg(currentIndex).arg(sum));
}

void frmMain::on_action_About_triggered()
{
	DlgIntroduction dlg;
	dlg.exec();
}

void frmMain::on_action_wiscom_triggered()
{
	//加载样式表
	QString qss;
	//QFile file(":/qss/psblack.css");
	//QFile file(":/qss/flatwhite.css");
	//QFile file(":/qss/lightblue.css");
	QFile file(":/qss/wiscom.css");
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
	App::CurrentSkin = 3;
	App::writeConfig();
}


void frmMain::on_treeWidget_Analysis_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	if(!current)
	{
		return;
	}
	QString str = current->data(0, Qt::UserRole).toString();

	ui->resulttext->setPlainText(str);

}


void frmMain::on_treeWidget_Analysis_customContextMenuRequested(const QPoint& pos)
{
	popMenu_Analysis->exec(QCursor::pos());
}

void frmMain::on_checkBox_simple_stateChanged(int arg1)
{
	if(arg1)
	{
		highlighter1->setEnable(false);
		highlighter2->setEnable(false);
	}
	else
	{
		highlighter1->setEnable(true);
		highlighter2->setEnable(true);
	}
}

void frmMain::on_checkBox_LineWrap_stateChanged(int arg1)
{
	if(arg1)
	{
		ui->resulttext->setLineWrapMode(QPlainTextEdit::WidgetWidth);
	}
	else
	{
		ui->resulttext->setLineWrapMode(QPlainTextEdit::NoWrap);
	}
}
