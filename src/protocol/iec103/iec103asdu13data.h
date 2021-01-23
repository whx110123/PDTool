#ifndef IEC103ASDU13DATA_H
#define IEC103ASDU13DATA_H

#include "iec103asdu.h"



class IEC103Asdu13Data : public IEC103AsduData
{
public:
	IEC103Asdu13Data();
	~IEC103Asdu13Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar rii;
	QString waveFileName;
	uint fileIndex;
	QTextCodec *gbk;
};

#endif // IEC103ASDU13DATA_H
