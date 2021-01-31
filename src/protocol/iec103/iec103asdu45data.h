#ifndef IEC103ASDU45DATA_H
#define IEC103ASDU45DATA_H

#include "iec103asdu44data.h"

class IEC103Asdu45Data : public IEC103Asdu44Data
{
public:
	IEC103Asdu45Data(const MyConfig& Config);
	~IEC103Asdu45Data();
	virtual bool handle(const QByteArray& buff);

public:

	QDateTime datetime;
};

#endif // IEC103ASDU45DATA_H
