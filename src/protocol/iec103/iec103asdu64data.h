﻿#ifndef IEC103ASDU64DATA_H
#define IEC103ASDU64DATA_H

#include "iec103asdu.h"



class IEC103Asdu64Data : public IEC103AsduData
{
public:
	IEC103Asdu64Data(const MyConfig& Config);
	~IEC103Asdu64Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar dcc;
};

#endif // IEC103ASDU64DATA_H
