﻿#ifndef IEC101ASDU3DATA_H
#define IEC101ASDU3DATA_H

#include "iec101asdu.h"

class IEC101Asdu3Data : public IEC101AsduData
{
public:
	IEC101Asdu3Data(const MyConfig& Config);
	~IEC101Asdu3Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar diq;
};

#endif // IEC101ASDU3DATA_H
