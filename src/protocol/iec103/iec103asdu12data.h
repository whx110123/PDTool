#ifndef IEC103ASDU12DATA_H
#define IEC103ASDU12DATA_H

#include "iec103asdu.h"



class IEC103Asdu12Data : public IEC103AsduData
{
public:
	IEC103Asdu12Data(const MyConfig& Config);
	~IEC103Asdu12Data();
	virtual bool handle(const QByteArray& buff);

public:
	uchar fpt;
	uchar jpt;
	float scl;
	uchar dpi_ch;
	ushort time_ch;
	float datafloat[24];	//故障前后三相电压与三相电流的幅值与相角，即Ua幅值相角、Ub幅值相角...
	QDateTime datetime;
	QString waveFileName;
	QString name;
	QDateTime rcvDataTime;
};

#endif // IEC103ASDU12DATA_H
