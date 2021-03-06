﻿#ifndef IEC101_H
#define IEC101_H

#include "iec101apci.h"
#include "iec101asdu.h"

class IEC101 : public MyBase
{
public:
	IEC101(const MyConfig& Config);
	~IEC101();
	virtual bool init(const QByteArray& buff);

public:
	IEC101Apci apci;
	IEC101Asdu asdu;
	uchar crc;
	uchar end;

};

#endif // IEC101_H
