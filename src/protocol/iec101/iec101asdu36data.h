#ifndef IEC101ASDU36DATA_H
#define IEC101ASDU36DATA_H

#include "iec101asdu14data.h"



class IEC101Asdu36Data : public IEC101Asdu14Data
{
public:
	IEC101Asdu36Data(const MyConfig& Config);
	~IEC101Asdu36Data();
	virtual bool handle(const QByteArray& buff);

};

#endif // IEC101ASDU36DATA_H
