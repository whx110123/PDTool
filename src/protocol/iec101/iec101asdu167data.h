#ifndef IEC101ASDU167DATA_H
#define IEC101ASDU167DATA_H
#include "iec101asdu.h"
#include "iec103asdu.h"

class IEC101Asdu167Data : public IEC101AsduData
{
public:
	IEC101Asdu167Data();
	~IEC101Asdu167Data();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	uchar ctrl;
	uchar devaddr[2];
	uchar iec103len;
	IEC103Asdu asdu;
private:
	QString ctrlToText();
};

#endif // IEC101ASDU167DATA_H
