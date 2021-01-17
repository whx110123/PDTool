#ifndef IEC103ASDU220DATA_H
#define IEC103ASDU220DATA_H

#include "iec103asdu.h"

class IEC103Asdu220Data : public IEC103AsduData
{
public:
	IEC103Asdu220Data();
	~IEC103Asdu220Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	QString typToText();
	uchar typ;
	QDateTime sDateTime;
	QDateTime eDateTime;
};

#endif // IEC103ASDU220DATA_H
