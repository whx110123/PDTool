#ifndef IEC101ASDU105DATA_H
#define IEC101ASDU105DATA_H

#include "iec101asdu104data.h"



class IEC101Asdu105Data : public IEC101Asdu104Data
{
public:
	IEC101Asdu105Data();
	~IEC101Asdu105Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC101ASDU105DATA_H
