#ifndef IEC101ASDU18DATA_H
#define IEC101ASDU18DATA_H

#include "iec101asdu.h"



class IEC101Asdu18Data : public IEC101AsduData
{
public:
	IEC101Asdu18Data();
	~IEC101Asdu18Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar spe;
	uchar qdp;
	QDateTime datetime1;
	QDateTime datetime2;
};

#endif // IEC101ASDU18DATA_H
