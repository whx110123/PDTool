#ifndef IEC103ASDU102DATA_H
#define IEC103ASDU102DATA_H

#include "iec103asdu101data.h"

struct NormalFileInfo
{
	QString fileName;
	QDateTime dt;
	uint fileSize;
};

class IEC103Asdu102Data : public IEC103Asdu101Data
{
public:
	IEC103Asdu102Data();
	~IEC103Asdu102Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar isLast;
	ushort fileNum;
	QVector<NormalFileInfo> files;
};

#endif // IEC103ASDU102DATA_H
