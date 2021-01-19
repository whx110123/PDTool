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
	ui->stackedWidget->setCurrentIndex(5);
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

}

void frmMain::initSignalAndSlots()
{
	connect(ui->action_Save, &QAction::triggered, this, &frmMain::SaveAll);
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

void frmMain::on_protocolcbox_currentIndexChanged(const QString &arg1)
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
        else if(arg1 == IEC_103BAOXINNET)
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

void frmMain::on_highlightEdit_textChanged(const QString &arg1)
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

void frmMain::on_pushButton_hide_clicked()
{
    if(ui->pushButton_hide->text() == "隐藏配置")
    {
        ui->pushButton_hide->setText("打开配置");
        ui->stackedWidget_config->hide();
    }
    else
    {
        ui->pushButton_hide->setText("隐藏配置");
        ui->stackedWidget_config->show();
    }
}

void frmMain::on_pushButton_clicked()
{
    modbusdlg->exec();
}
