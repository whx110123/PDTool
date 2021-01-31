#ifndef IEC101ASDU43DATA_H
#define IEC101ASDU43DATA_H

#include "iec101asdu.h"



class IEC101Asdu43Data : public IEC101AsduData
{
public:
	IEC101Asdu43Data(const MyConfig& Config);
	~IEC101Asdu43Data();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();

public:
	uchar cont;
	uint fileindex;
	QString filedata;
	uchar crc;
private:
	QString contToText();
};

#endif // IEC101ASDU43DATA_H
