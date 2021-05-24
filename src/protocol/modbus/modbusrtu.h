#ifndef MODBUSRTU_H
#define MODBUSRTU_H

#include "modbus.h"



class ModbusRTU : public MyBase
{
public:
	ModbusRTU(const MyConfig& Config);
	~ModbusRTU();
	virtual bool init(const QByteArray& buff);					//初始化

public:
	Modbus mb;
	ushort crc;
};

#endif // MODBUSRTU_H
