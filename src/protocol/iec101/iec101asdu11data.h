#ifndef IEC101ASDU11DATA_H
#define IEC101ASDU11DATA_H

#include "iec101asdu9data.h"



class IEC101Asdu11Data : public IEC101Asdu9Data
{
public:
	IEC101Asdu11Data();
	~IEC101Asdu11Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC101ASDU11DATA_H
