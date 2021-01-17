#ifndef IEC101ASDU20DATA_H
#define IEC101ASDU20DATA_H

#include "iec101asdu.h"



class IEC101Asdu20Data : public IEC101AsduData
{
public:
	IEC101Asdu20Data();
	~IEC101Asdu20Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QString yx16ToText();
	QString yx16FlagToText();
	ushort yx16;
	ushort yx16flag;
	uchar qds;
};

#endif // IEC101ASDU20DATA_H
