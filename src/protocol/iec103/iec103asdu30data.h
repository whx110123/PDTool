#ifndef IEC103ASDU30DATA_H
#define IEC103ASDU30DATA_H

#include "iec103asdu.h"

class IEC103Asdu30Data : public IEC103AsduData
{
public:
	IEC103Asdu30Data();
	~IEC103Asdu30Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar datauchar;
	uchar tov;
	ushort fan;
	uchar acc;
	uchar ndv;
	ushort nfe;
	QVector<short> sdvs;
};

#endif // IEC103ASDU30DATA_H
