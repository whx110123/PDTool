#ifndef IEC103ASDU105DATA_H
#define IEC103ASDU105DATA_H

#include "iec103asdu.h"



class IEC103Asdu105Data : public IEC103AsduData
{
public:
	IEC103Asdu105Data();
	~IEC103Asdu105Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar rii;
	uchar flag;
	QString fileName;
	QDateTime dt;
	uint fileSize;
	QTextCodec *gbk;
};

#endif // IEC103ASDU105DATA_H
