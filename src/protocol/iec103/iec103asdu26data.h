#ifndef IEC103ASDU26DATA_H
#define IEC103ASDU26DATA_H

#include "iec103asdu.h"

class IEC103Asdu26Data : public IEC103AsduData
{
public:
	IEC103Asdu26Data();
	~IEC103Asdu26Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar datauchar;
	uchar tov;
	ushort fan;
	ushort nof;
	uchar noc;
	ushort noe;
	ushort _int;
	QDateTime datetime;
};

#endif // IEC103ASDU26DATA_H
