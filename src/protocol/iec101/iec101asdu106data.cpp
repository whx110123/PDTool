#include "iec101asdu106data.h"

IEC101Asdu106Data::IEC101Asdu106Data(const MyConfig& Config): IEC101Asdu103Data(Config)
{

}

IEC101Asdu106Data::~IEC101Asdu106Data()
{

}

bool IEC101Asdu106Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	datetime = charToDateTime(buff.data() + len, 2, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 2));
	len += 2;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

