#include "dialogmodbus.h"
#include "ui_dialogmodbus.h"

DialogModbus::DialogModbus(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogModbus)
{
	ui->setupUi(this);
	initShow();
	addItems();
}

DialogModbus::~DialogModbus()
{
	delete ui;
}

void DialogModbus::initShow()
{
	QTableWidgetItem    *headerItem;
	QStringList headerText;
	headerText << "类型" << "解析码" << "字节数" << "描述"; //表头标题用QStringList来表示
	ui->tableInfo->setColumnCount(headerText.count());//列数设置为与 headerText的行数相等
	QHeaderView *header = ui->tableInfo->horizontalHeader();
	header->setSectionResizeMode(QHeaderView::ResizeToContents);//自动宽度
	header->setStretchLastSection(true);
	for(int i = 0; i < ui->tableInfo->columnCount(); i++) //列编号从0开始
	{
		headerItem = new QTableWidgetItem(headerText.at(i)); //新建一个QTableWidgetItem， headerText.at(i)获取headerText的i行字符串
		QFont font = headerItem->font(); //获取原有字体设置
		font.setBold(true);//设置为粗体
		font.setPointSize(12);//字体大小
		headerItem->setTextColor(Qt::red);//字体颜色
		headerItem->setFont(font);//设置字体
		ui->tableInfo->setHorizontalHeaderItem(i, headerItem); //设置表头单元格的Item
	}
	ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectRows); //选择行
	ui->tableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); //不允许编辑
	ui->tableInfo->setAlternatingRowColors(true); //设置交替行背景颜色
}

void DialogModbus::addItems()
{

	addItem(QStringList() << "遥测" << "0" << "2字节" << "有符号整数");
	addItem(QStringList() << "遥测" << "1" << "2字节" << "无符号整数");
	addItem(QStringList() << "遥测" << "2" << "2字节" << "原码表示，最高位为符号位");
	addItem(QStringList() << "遥测" << "3" << "4字节" << "有符号整数");
	addItem(QStringList() << "遥测" << "4" << "4字节" << "无符号整数");
	addItem(QStringList() << "遥测" << "5" << "4字节" << "浮点数");
	addItem(QStringList() << "遥测" << "6" << "1字节" << "有符号整数");
	addItem(QStringList() << "遥测" << "7" << "1字节" << "无符号整数");
//	addItem(QStringList() << "遥测" << "8" << "1字节" << "有符号整数");
//	addItem(QStringList() << "遥测" << "9" << "2字节" << "有符号整数");
	addItem(QStringList() << "遥测" << "A" << "8字节" << "双精度浮点数");
	addItem(QStringList() << "遥测" << "F" << "2字节" << "忽略2个字节");
	addItem(QStringList() << "遥信" << "0" << "1字节" << "从低位开始读");
	addItem(QStringList() << "遥信" << "1" << "2字节" << "从低字节低位开始读");
	addItem(QStringList() << "遥信" << "2" << "4字节" << "从低字节低位开始读");
	addItem(QStringList() << "遥信" << "3" << "1字节" << "从高位开始读");
//	addItem(QStringList() << "遥信" << "4" << "1字节" << "有符号整数");
//	addItem(QStringList() << "遥信" << "5" << "2字节" << "有符号整数");
	addItem(QStringList() << "遥信" << "F" << "1字节" << "忽略1个字节");
	addItem(QStringList() << "遥脉" << "0" << "4字节" << "无符号整数");
	addItem(QStringList() << "遥脉" << "1" << "4字节" << "浮点数");
	addItem(QStringList() << "遥脉" << "F" << "4字节" << "忽略4个字节");

}

void DialogModbus::addItem(QStringList list)
{
	int curRow = ui->tableInfo->rowCount(); //当前行号
	ui->tableInfo->insertRow(curRow);//在表格尾部添加一行
	setItem(curRow, list);
}

void DialogModbus::setItem(int rowNo, QStringList list)
{
	QTableWidgetItem *item;
	QColor color(Qt::white);
	QString type = list.at(0);
	QString analy = list.at(1);
	QString len = list.at(2);
	QString des = list.at(3);
	if(type == "遥测")
	{
		color = Qt::cyan;
	}
	else if(type == "遥信")
	{
		color = Qt::green;
	}
	else if(type == "遥脉")
	{
		color = Qt::gray;
	}
	item = new QTableWidgetItem(type);
	item->setBackgroundColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
	ui->tableInfo->setItem(rowNo, DialogModbus::colType, item); //为单元格设置Item

	item = new QTableWidgetItem(analy);
	item->setBackgroundColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
	ui->tableInfo->setItem(rowNo, DialogModbus::colAnaly, item); //为单元格设置Item

	item = new QTableWidgetItem(len);
	item->setBackgroundColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //文本对齐格式
	ui->tableInfo->setItem(rowNo, DialogModbus::colLen, item); //为单元格设置Item

	item = new QTableWidgetItem(des);
	item->setBackgroundColor(color);
	item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter); //文本对齐格式
	ui->tableInfo->setItem(rowNo, DialogModbus::colDes, item); //为单元格设置Item
}
