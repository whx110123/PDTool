﻿#ifndef IEC103ASDU34DATA_H
#define IEC103ASDU34DATA_H

#include "iec103asdu32data.h"



class IEC103Asdu34Data : public IEC103Asdu32Data
{
public:
	IEC103Asdu34Data(const MyConfig& Config);
	~IEC103Asdu34Data();
	virtual bool handle(const QByteArray& buff);
};

#endif // IEC103ASDU34DATA_H
