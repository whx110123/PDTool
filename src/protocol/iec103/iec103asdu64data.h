#ifndef IEC103ASDU64DATA_H
#define IEC103ASDU64DATA_H

#include "iec103asdu.h"



class IEC103Asdu64Data : public IEC103AsduData
{
public:
	IEC103Asdu64Data();
	~IEC103Asdu64Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar dcc;
};

#endif // IEC103ASDU64DATA_H
