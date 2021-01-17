#ifndef MODBUSRTU_H
#define MODBUSRTU_H

#include "modbus.h"



class ModbusRTU : public MyBase
{
public:
	ModbusRTU();
	~ModbusRTU();
	virtual bool init(const QByteArray& buff);					//初始化
	virtual QString showToText();						//显示解析结果

public:
	Modbus mb;
	ushort crc;
};

#endif // MODBUSRTU_H
