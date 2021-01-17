#ifndef IEC101ASDU43DATA_H
#define IEC101ASDU43DATA_H

#include "iec101asdu.h"



class IEC101Asdu43Data : public IEC101AsduData
{
public:
	IEC101Asdu43Data();
	~IEC101Asdu43Data();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	uchar cont;
	uint fileindex;
	QString filedata;
	uchar crc;
private:
	QString contToText();
};

#endif // IEC101ASDU43DATA_H
