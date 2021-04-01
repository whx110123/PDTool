#include "iec103asdu23data.h"

IEC103Asdu23Data::IEC103Asdu23Data(const MyConfig& Config): IEC103AsduData(Config)
{

}

IEC103Asdu23Data::~IEC103Asdu23Data()
{

}

bool IEC103Asdu23Data::handle(const QByteArray& buff)
{
	fan = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	len += 2;

	sof = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + sofToText(sof) + "\r\n");
	len++;


	datetime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

