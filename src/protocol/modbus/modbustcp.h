#ifndef MODBUSTCP_H
#define MODBUSTCP_H

#include "modbus.h"

class ModbusTCP : public MyBase
{
public:
	ModbusTCP();
	~ModbusTCP();
	virtual bool init(const QByteArray& buff);			//初始化
	virtual QString showToText();						//显示解析结果

public:
	ushort flagIndex;		//事务处理标识 ：可以理解为报文的序列号，一般每次通信之后就要加1以区别不同的通信数据报文。
	ushort flag;			//协议标识符 ：00 00表示ModbusTCP协议。
	ushort length;			//长度 ：表示接下来的数据长度，单位为字节。
	Modbus mb;

};

#endif // MODBUSTCP_H
