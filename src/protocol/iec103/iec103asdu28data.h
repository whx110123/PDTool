#ifndef IEC103ASDU28DATA_H
#define IEC103ASDU28DATA_H

#include "iec103asdu.h"

class IEC103Asdu28Data : public IEC103AsduData
{
public:
	IEC103Asdu28Data();
	~IEC103Asdu28Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar datauchar1;
	uchar datauchar2;
	ushort fan;
};

#endif // IEC103ASDU28DATA_H
