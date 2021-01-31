#ifndef IEC101ASDU40DATA_H
#define IEC101ASDU40DATA_H

#include "iec101asdu19data.h"



class IEC101Asdu40Data : public IEC101Asdu19Data
{
public:
	IEC101Asdu40Data(const MyConfig& Config);
	~IEC101Asdu40Data();
	virtual bool handle(const QByteArray& buff);
};

#endif // IEC101ASDU40DATA_H
