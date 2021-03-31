#ifndef IEC104_H
#define IEC104_H

#include "iec104apci.h"
#include "iec101asdu.h"

class IEC104 : public MyBase
{
public:
	IEC104(const MyConfig& Config);
	~IEC104();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(MyData& proData);

public:
	IEC104Apci apci;
	IEC101Asdu asdu;
};

#endif // IEC104_H
