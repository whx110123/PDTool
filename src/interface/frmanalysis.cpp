#include "frmanalysis.h"
#include "ui_frmanalysis.h"
#include "quiwidget.h"
#include <QString>
#include <app.h>
#include <iec101.h>
#include <iec103com.h>
#include <iec103netbaoxin.h>
#include <iec103netwiscom.h>
#include <measuredterminal.h>
#include <modbusrtu.h>
#include <modbustcp.h>
#include "myhighlighter.h"
#include "iec104.h"


frmAnalysis::frmAnalysis(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmAnalysis)
{
	ui->setupUi(this);
	highlighter1 = new myhighlighter(ui->resulttext->document());
	highlighter2 = new myhighlighter(ui->originaltext->document());
	modbusdlg = new DialogModbus(this);
	initForm();
	initConfig();
}

frmAnalysis::~frmAnalysis()
{
	delete highlighter1;
	delete highlighter2;
	qDeleteAll(MyBase::mConfig.groups);
	MyBase::mConfig.groups.clear();
	delete ui;
}

void frmAnalysis::initForm()
{
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
}

void frmAnalysis::initConfig()
{
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
	ui->stackedWidget_protocol->setCurrentIndex(0);
	ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
	ui->comboBox_addrlen->setCurrentText("1");
	ui->comboBox_cotlen->setCurrentText("2");
	ui->comboBox_comaddrlen->setCurrentText("2");
	ui->comboBox_infaddrlen->setCurrentText("3");
	highlighter1->hlformat.setForeground(Qt::magenta);
	highlighter1->hlformat.setFontWeight(QFont::Bold);
	highlighter2->hlformat.setForeground(Qt::magenta);
	highlighter2->hlformat.setFontWeight(QFont::Bold);
	//    connect(ui->protocolcbox, SIGNAL(currentIndexChanged(int)), this, SLOT(saveConfig()));
}

void frmAnalysis::on_clearBtn_clicked()
{
	ui->originaltext->clear();
	ui->resulttext->clear();
}

void frmAnalysis::on_protocolcbox_currentIndexChanged(const QString& arg1)
{
	if(arg1 == IEC_104)
	{
		ui->stackedWidget_protocol->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("2");
		ui->comboBox_comaddrlen->setCurrentText("2");
		ui->comboBox_infaddrlen->setCurrentText("3");
	}
	else if(arg1 == IEC_101)
	{
		ui->stackedWidget_protocol->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLESAME);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("2");
	}
	else if(arg1 == IEC_103WISCOMNET)
	{
		ui->stackedWidget_protocol->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == IEC_103COM)
	{
		ui->stackedWidget_protocol->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLESAME);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == IEC_103ASDU || arg1 == IEC_103NANZINET)
	{
		ui->stackedWidget_protocol->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == IEC_103BAOXINNET)
	{
		ui->stackedWidget_protocol->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("2");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == IEC_103XUJINET)
	{
		ui->stackedWidget_protocol->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("2");
		ui->comboBox_comaddrlen->setCurrentText("2");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == IEC_103HUABEI)
	{
		ui->stackedWidget_protocol->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(arg1 == MODBUS_RTU || arg1 == MODBUS_TCP)
	{
		ui->stackedWidget_protocol->setCurrentIndex(1);
	}
	else if(arg1 == MEASUREDTERMINAL_NW_NET)
	{
		ui->stackedWidget_protocol->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("7");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
}

void frmAnalysis::on_highlightEdit_textChanged(const QString& arg1)
{
	highlighter1->hlstr = arg1;
	highlighter2->hlstr = arg1;
	ui->resulttext->setText(ui->resulttext->toPlainText());
	ui->originaltext->setText(ui->originaltext->toPlainText());
}


void frmAnalysis::on_fontcolor_clicked()
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

void frmAnalysis::on_backgroundcolor_clicked()
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


void frmAnalysis::on_fontchange_clicked()
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

//void frmAnalysis::on_AnalysisBtn_clicked()
//{
//	ui->resulttext->clear();
//	App::readConfig();
//	QString data = ui->originaltext->toPlainText();
//	if(data.length() <= 0)
//	{
//		return;
//	}
//	QByteArray buffer;
//	buffer = QUIHelper::hexStrToByteArray(data);
//	int err;
//	QString text;
//	/************************************************************/
//	int i = 1;
//	while(!buffer.isEmpty())
//	{
//		text.append(QString("####第%1帧####\r\n").arg(i++));
//		if(ui->protocolcbox->currentText() == IEC_104)           //分析104报文
//		{
//			m_104 = new protocol101::protocol104apdu;
//			m_104->cotlen = ui->comboBox_cotlen->currentText().toInt();
//			m_104->comaddrlen = ui->comboBox_comaddrlen->currentText().toInt();
//			m_104->dataaddrlen = ui->comboBox_infaddrlen->currentText().toInt();
//			err = m_104->CharT0APDU(buffer.data(), buffer.length());
//			buffer.remove(0, m_104->m_apdu->length);
//			if(err)
//			{
//				text.append(m_104->dealERR(err));
//				break;
//			}
//			else
//			{
//				text.append(m_104->dealAPDU());
//			}
//			delete m_104;

//		}
//		else if(ui->protocolcbox->currentText() == IEC_101)      //分析101报文
//		{
//			m_101 = new protocol101::protocol101apdu;
//			m_101->cotlen = ui->comboBox_cotlen->currentText().toInt();
//			m_101->comaddrlen = ui->comboBox_comaddrlen->currentText().toInt();
//			m_101->dataaddrlen = ui->comboBox_infaddrlen->currentText().toInt();
//			err = m_101->CharT0APDU(buffer.data(), buffer.length());
//			buffer.remove(0, m_101->m_apdu->length);
//			if(err)
//			{
//				text.append(m_101->dealERR(err));
//				break;
//			}
//			else
//			{
//				text.append(m_101->dealAPDU());
//			}
//			delete m_101;
//		}
//		else if(ui->protocolcbox->currentText() == IEC_103WISCOMNET)//分析金智网络103报文
//		{
//			m_103wiscomnet = new protocol103::protocol103wiscomnet;
//			err = m_103wiscomnet->CharT0APDU(buffer.data(), buffer.length());
//			buffer.remove(0, m_103wiscomnet->m_apdu->length);
//			if(err)
//			{
//				text.append(m_103wiscomnet->dealERR(err));
//				break;
//			}
//			else
//			{
//				text.append(m_103wiscomnet->dealAPDU());
//			}
//			delete m_103wiscomnet;
//		}
//		else if(ui->protocolcbox->currentText() == IEC_103COM)
//		{
//			m_103com = new protocol103::protocol103com;
//			err = m_103com->CharT0APDU(buffer.data(), buffer.length());
//			buffer.remove(0, m_103com->m_apdu->length);
//			if(err)
//			{
//				text.append(m_103com->dealERR(err));
//				break;
//			}
//			else
//			{
//				text.append(m_103com->dealAPDU());
//			}
//			delete m_103com;
//		}
//		else
//		{
//			break;
//		}
//	}
//	ui->resulttext->setText(text);
//	return;
//}

void frmAnalysis::on_pushButton_Analysis_clicked()
{
	ui->resulttext->clear();
	App::readConfig();
	QString data = ui->originaltext->toPlainText();
	if(data.length() <= 0)
	{
		return;
	}

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


void frmAnalysis::on_pushButton_change_clicked()
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

void frmAnalysis::on_pushButton_clean_clicked()
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

bool frmAnalysis::eventFilter(QObject *obj, QEvent *event)
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
		if(event->type() == QEvent::Wheel)
		{
			return true;
		}

	}

	return QWidget::eventFilter(obj, event);

}

void frmAnalysis::on_pushButton_clicked()
{
	modbusdlg->exec();
}

void frmAnalysis::initProtocolConfig()
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

MyBase *frmAnalysis::createByName(QString name)
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
	else if(name == IEC_103BAOXINNET || name == IEC_103XUJINET)
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

	if(protocol)
	{
		protocol->protocolName = ui->protocolcbox->currentText();
	}
	return protocol;
}
