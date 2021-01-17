#include "iec103asdu8data.h"

IEC103Asdu8Data::IEC103Asdu8Data()
{

}
IEC103Asdu8Data::~IEC103Asdu8Data()
{

}

bool IEC103Asdu8Data::handle(const QByteArray& buff)
{
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu8Data::createData(IECDataConfig& config)
{
	return true;
}
