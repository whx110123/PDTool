#ifndef IEC103ASDU103DATA_H
#define IEC103ASDU103DATA_H

#include "iec103asdu.h"



class IEC103Asdu103Data : public IEC103AsduData
{
public:
	IEC103Asdu103Data(const MyConfig& Config);
	~IEC103Asdu103Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar rii;
	QString fileName;
	uint fileIndex;
	QTextCodec *gbk;
};

#endif // IEC103ASDU103DATA_H
