#ifndef IEC104ASDU167DATA_H
#define IEC104ASDU167DATA_H
#include "iec101asdu.h"
#include "iec103asdu.h"


//定值处理(扩展功能)
class IEC104Asdu167Data : public IEC101AsduData
{
public:
	IEC104Asdu167Data(const MyConfig& Config);
	~IEC104Asdu167Data();
	virtual bool init(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	uchar ctrl;
	uchar devaddr[2];
	uchar iec103len;
	IEC103Asdu asdu;
private:
	QString ctrlToText();
};

#endif // IEC104ASDU167DATA_H
