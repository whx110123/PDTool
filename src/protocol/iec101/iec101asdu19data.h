#ifndef IEC101ASDU19DATA_H
#define IEC101ASDU19DATA_H

#include "iec101asdu.h"



class IEC101Asdu19Data : public IEC101AsduData
{
public:
	IEC101Asdu19Data();
	~IEC101Asdu19Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar oci;
	uchar qdp;
	QDateTime datetime1;
	QDateTime datetime2;
};

#endif // IEC101ASDU19DATA_H
