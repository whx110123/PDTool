#ifndef IEC103ASDU105DATA_H
#define IEC103ASDU105DATA_H

#include "iec103asdu.h"



class IEC103Asdu105Data : public IEC103AsduData
{
public:
	IEC103Asdu105Data(const MyConfig& Config);
	~IEC103Asdu105Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar reportNum;
	QStringList fileNames;
	QDateTime dt;
	QTextCodec *gbk;
	/*南网使用*/
	uchar rii;
	uchar flag;
	QString fileName;
	uint fileSize;

};

#endif // IEC103ASDU105DATA_H
