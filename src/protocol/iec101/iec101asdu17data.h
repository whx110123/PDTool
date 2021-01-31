#ifndef IEC101ASDU17DATA_H
#define IEC101ASDU17DATA_H

#include "iec101asdu.h"



class IEC101Asdu17Data : public IEC101AsduData
{
public:
	IEC101Asdu17Data(const MyConfig& Config);
	~IEC101Asdu17Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar sep;
	QDateTime datetime1;
	QDateTime datetime2;
};

#endif // IEC101ASDU17DATA_H
