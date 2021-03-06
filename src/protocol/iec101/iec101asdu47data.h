﻿#ifndef IEC101ASDU47DATA_H
#define IEC101ASDU47DATA_H

#include "iec101asdu.h"



class IEC101Asdu47Data : public IEC101AsduData
{
public:
	IEC101Asdu47Data(const MyConfig& Config);
	~IEC101Asdu47Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	uchar rco;
};

#endif // IEC101ASDU47DATA_H
