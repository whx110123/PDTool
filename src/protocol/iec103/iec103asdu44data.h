#ifndef IEC103ASDU44DATA_H
#define IEC103ASDU44DATA_H

#include "iec103asdu.h"

class IEC103Asdu44Data : public IEC103AsduData
{
public:
	IEC103Asdu44Data();
	~IEC103Asdu44Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QString yx16ToText();
	QString yx16FlagToText();
	ushort yx16;
	ushort yx16flag;
	uchar qds;
};

#endif // IEC103ASDU44DATA_H
