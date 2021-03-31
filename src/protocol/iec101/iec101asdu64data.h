#ifndef IEC101ASDU64DATA_H
#define IEC101ASDU64DATA_H

#include "iec101asdu51data.h"



class IEC101Asdu64Data : public IEC101Asdu51Data
{
public:
	IEC101Asdu64Data(const MyConfig& Config);
	~IEC101Asdu64Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU64DATA_H
