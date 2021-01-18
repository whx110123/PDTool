//#pragma execution_character_set("utf-8")
#include "frmmain.h"
#include "ui_frmmain.h"
#include "qfile.h"
#include "qtextstream.h"
#include "qtranslator.h"
#include "qdesktopwidget.h"
#include "qdebug.h"

frmMain::frmMain(QWidget *parent) : QMainWindow(parent), ui(new Ui::frmMain)
{
	ui->setupUi(this);
	this->initForm();
}

frmMain::~frmMain()
{
	delete ui;
}

void frmMain::showEvent(QShowEvent *)
{
//    int width = ui->tabConfig->width() / ui->tabConfig->count() - 20;
//    ui->tabConfig->setStyleSheet(QString("QTabBar::tab{min-width:%1px;}").arg(width));
}

void frmMain::initForm()
{
	this->initSignalAndSlots();
	this->initTableWidget();
	this->initTreeWidget();
	this->initListWidget();
	this->initOther();
	this->initStyle();
	this->initTranslator();
	ui->stackedWidget->setCurrentIndex(5);
	ui->stackedWidget_config->setCurrentIndex(0);

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


	ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
	ui->comboBox_addrlen->setCurrentText("1");
	ui->comboBox_cotlen->setCurrentText("2");
	ui->comboBox_comaddrlen->setCurrentText("2");
	ui->comboBox_infaddrlen->setCurrentText("3");

}

void frmMain::initSignalAndSlots()
{
	connect(ui->action_Save, &QAction::triggered, this, &frmMain::SaveAll);
	connect(ui->page_analysis, &frmAnalysis::emitstr, this, &frmMain::HandleStr);
}

void frmMain::initTableWidget()
{
	//设置列数和列宽
//    int width = qApp->desktop()->availableGeometry().width() - 120;
//    ui->tableWidget->setColumnCount(5);
//    ui->tableWidget->setColumnWidth(0, width * 0.06);
//    ui->tableWidget->setColumnWidth(1, width * 0.10);
//    ui->tableWidget->setColumnWidth(2, width * 0.06);
//    ui->tableWidget->setColumnWidth(3, width * 0.10);
//    ui->tableWidget->setColumnWidth(4, width * 0.15);
//    ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);

//    QStringList headText;
//    headText << "设备编号" << "设备名称" << "设备地址" << "告警内容" << "告警时间";
//    ui->tableWidget->setHorizontalHeaderLabels(headText);
//    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->tableWidget->setAlternatingRowColors(true);
//    ui->tableWidget->verticalHeader()->setVisible(false);
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

//    //设置行高
//    ui->tableWidget->setRowCount(300);

//    for (int i = 0; i < 300; i++) {
//        ui->tableWidget->setRowHeight(i, 24);

//        QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(i + 1));
//        QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString("测试设备%1").arg(i + 1));
//        QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(i + 1));
//        QTableWidgetItem *itemContent = new QTableWidgetItem("防区告警");
//        QTableWidgetItem *itemTime = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

//        ui->tableWidget->setItem(i, 0, itemDeviceID);
//        ui->tableWidget->setItem(i, 1, itemDeviceName);
//        ui->tableWidget->setItem(i, 2, itemDeviceAddr);
//        ui->tableWidget->setItem(i, 3, itemContent);
//        ui->tableWidget->setItem(i, 4, itemTime);
//    }
}

void frmMain::initTreeWidget()
{
//    ui->treeWidget->clear();
//    ui->treeWidget->setHeaderLabel(" 树状列表控件");

//    QTreeWidgetItem *group1 = new QTreeWidgetItem(ui->treeWidget);
//    group1->setText(0, "父元素1");
//    group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//    group1->setCheckState(0, Qt::PartiallyChecked);

//    QTreeWidgetItem *subItem11 = new QTreeWidgetItem(group1);
//    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//    subItem11->setText(0, "子元素1");
//    subItem11->setCheckState(0, Qt::Checked);

//    QTreeWidgetItem *subItem12 = new QTreeWidgetItem(group1);
//    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//    subItem12->setText(0, "子元素2");
//    subItem12->setCheckState(0, Qt::Unchecked);

//    QTreeWidgetItem *subItem13 = new QTreeWidgetItem(group1);
//    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//    subItem13->setText(0, "子元素3");
//    subItem13->setCheckState(0, Qt::Unchecked);

//    QTreeWidgetItem *group2 = new QTreeWidgetItem(ui->treeWidget);
//    group2->setText(0, "父元素2");
//    group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//    group2->setCheckState(0, Qt::Unchecked);

//    QTreeWidgetItem *subItem21 = new QTreeWidgetItem(group2);
//    subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//    subItem21->setText(0, "子元素1");
//    subItem21->setCheckState(0, Qt::Unchecked);

//    QTreeWidgetItem *subItem211 = new QTreeWidgetItem(subItem21);
//    subItem211->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//    subItem211->setText(0, "子子元素1");
//    subItem211->setCheckState(0, Qt::Unchecked);

//    ui->treeWidget->expandAll();
}

void frmMain::initListWidget()
{
//    QStringList items;
//    for (int i = 1; i <= 30; i++) {
//        items << QString("元素%1").arg(i);
//    }

//    ui->listWidget->addItems(items);
//    ui->cbox1->addItems(items);
//    ui->cbox2->addItems(items);
}

void frmMain::initOther()
{
//    ui->rbtn1->setChecked(true);
//    ui->ck2->setChecked(true);
//    ui->ck3->setCheckState(Qt::PartiallyChecked);
//    ui->horizontalSlider->setValue(88);

//    ui->tab9->setStyleSheet("QPushButton{font:20pt;}");
//    ui->widgetVideo->setStyleSheet("QLabel{font:20pt;}");

//    ui->widgetLeft->setProperty("nav", "left");
//    ui->widgetBottom->setProperty("form", "bottom");
//    ui->widgetTop->setProperty("nav", "top");
//    ui->widgetVideo->setProperty("video", true);

//    QList<QLabel *> labChs = ui->widgetVideo->findChildren<QLabel *>();
//    foreach (QLabel *lab, labChs) {
//        lab->setFocusPolicy(Qt::StrongFocus);
//    }
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

void frmMain::HandleStr(QString str)
{
	if(str == IEC_104)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("2");
		ui->comboBox_comaddrlen->setCurrentText("2");
		ui->comboBox_infaddrlen->setCurrentText("3");
	}
	else if(str == IEC_101)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLESAME);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("2");
	}
	else if(str == IEC_103WISCOMNET)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(str == IEC_103COM)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLESAME);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(str == IEC_103ASDU || str == IEC_103NANZINET)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(str == IEC_103BAOXINNET)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("2");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(str == IEC_103XUJINET)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_SINGLE);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("2");
		ui->comboBox_comaddrlen->setCurrentText("2");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(str == IEC_103HUABEI)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("1");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
	else if(str == MODBUS_RTU || str == MODBUS_TCP)
	{
		ui->stackedWidget_config->setCurrentIndex(1);
	}
	else if(str == MEASUREDTERMINAL_NW_NET)
	{
		ui->stackedWidget_config->setCurrentIndex(0);
		ui->comboBox_lengthtype->setCurrentText(IEC_DOUBLEDIFF);
		ui->comboBox_addrlen->setCurrentText("7");
		ui->comboBox_cotlen->setCurrentText("1");
		ui->comboBox_comaddrlen->setCurrentText("1");
		ui->comboBox_infaddrlen->setCurrentText("1");
	}
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
