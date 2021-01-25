#ifndef IEC103ASDU101DATA_H
#define IEC103ASDU101DATA_H

#include "iec103asdu15data.h"



class IEC103Asdu101Data : public IEC103Asdu15Data
{
public:
	IEC103Asdu101Data();
	~IEC103Asdu101Data();
	virtual bool handle(const QByteArray& buff);

public:
	QString fileName;
	QTextCodec *gbk;
};

#endif // IEC103ASDU101DATA_H
