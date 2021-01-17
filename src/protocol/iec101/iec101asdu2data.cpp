#include "iec101asdu2data.h"

IEC101Asdu2Data::IEC101Asdu2Data()
{

}

IEC101Asdu2Data::~IEC101Asdu2Data()
{

}

bool IEC101Asdu2Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	siq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + spiToText(siq) + "   " + ivToText(siq) + "   " + ntToText(siq) + "   " + sbToText(siq) + "   " + blToText(siq) + "\r\n");
	len++;

	datetime = charToDateTime(buff.data() + len, 3, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 3));
	len += 3;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu2Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
