#ifndef IEC101ASDU39DATA_H
#define IEC101ASDU39DATA_H

#include "iec101asdu18data.h"



class IEC101Asdu39Data : public IEC101Asdu18Data
{
public:
	IEC101Asdu39Data();
	~IEC101Asdu39Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC101ASDU39DATA_H
