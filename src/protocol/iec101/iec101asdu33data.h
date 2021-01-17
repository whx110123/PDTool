#ifndef IEC101ASDU33DATA_H
#define IEC101ASDU33DATA_H

#include "iec101asdu8data.h"



class IEC101Asdu33Data : public IEC101Asdu8Data
{
public:
	IEC101Asdu33Data();
	~IEC101Asdu33Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);
};

#endif // IEC101ASDU33DATA_H
