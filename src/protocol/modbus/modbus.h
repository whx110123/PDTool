#ifndef MODBUS_H
#define MODBUS_H

#include "modbusdata.h"

class Modbus : public MyBase
{
public:
	Modbus();
	~Modbus();
	virtual bool init(const QByteArray& buff);			//初始化
	virtual QString showToText();						//显示解析结果

public:
	QString codeToText();
	bool isMaster;			//召唤或应答
	uchar addr;				//设备地址
	uchar code;				//功能码

	ushort dataAddr;		//起始地址
	ushort data_num;		//召唤个数,一般为寄存器数量
	uchar bytenum;			//数据字节数

	ModbusDataGroup mgroup;				//根据报文实际长度，选择解析方式
	QList<ModbusData *> datalist;		//应答报文数据集合
};

#endif // MODBUS_H
