#ifndef IEC103ASDU46DATA_H
#define IEC103ASDU46DATA_H

#include "iec103asdu.h"

class IEC103Asdu46Data : public IEC103AsduData
{
public:
	IEC103Asdu46Data();
	~IEC103Asdu46Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QString yx8ToText();
	QString yx8FlagToText();

	ushort yx8;
	ushort yx8flag;
	uchar qds;
};

#endif // IEC103ASDU46DATA_H
