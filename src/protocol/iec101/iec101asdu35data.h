﻿#ifndef IEC101ASDU35DATA_H
#define IEC101ASDU35DATA_H

#include "iec101asdu12data.h"



class IEC101Asdu35Data : public IEC101Asdu12Data
{
public:
	IEC101Asdu35Data(const MyConfig& Config);
	~IEC101Asdu35Data();
	virtual bool handle(const QByteArray& buff);
};

#endif // IEC101ASDU35DATA_H
