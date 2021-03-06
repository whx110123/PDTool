﻿#ifndef IEC103ASDU39DATA_H
#define IEC103ASDU39DATA_H

#include "iec103asdu38data.h"



class IEC103Asdu39Data : public IEC103Asdu38Data
{
public:
	IEC103Asdu39Data(const MyConfig& Config);
	~IEC103Asdu39Data();
	virtual bool handle(const QByteArray& buff);

public:

	QDateTime datetime;
};

#endif // IEC103ASDU39DATA_H
