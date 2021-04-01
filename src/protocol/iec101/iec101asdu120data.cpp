#include "iec101asdu120data.h"

IEC101Asdu120Data::IEC101Asdu120Data(const MyConfig& Config): IEC101AsduData(Config)
{
	frq = 0;
}

IEC101Asdu120Data::~IEC101Asdu120Data()
{

}

bool IEC101Asdu120Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	frq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + frqToText(frq) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

