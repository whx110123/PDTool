#include "iec101asdu38data.h"

IEC101Asdu38Data::IEC101Asdu38Data()
{

}

IEC101Asdu38Data::~IEC101Asdu38Data()
{

}

bool IEC101Asdu38Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	sep = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t继电保护的单个事件SEP:" + esToText(sep) + "   " + ivToText(sep) + "   " + ntToText(sep) + "   " + sbToText(sep) + "   " + blToText(sep) + "   " + eiToText(sep) + "\r\n");
	len++;

	datetime1 = charToDateTime(buff.data() + len, 2, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 2));
	len += 2;

	datetime2 = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu38Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
