#include "iec103asdu17data.h"

IEC103Asdu17Data::IEC103Asdu17Data()
{

}

IEC103Asdu17Data::~IEC103Asdu17Data()
{

}

bool IEC103Asdu17Data::handle(const QByteArray& buff)
{
	if(protocolName == IEC_103BAOXINNET_NW)
	{
		rii = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
		len++;
	}

	eventType = *(buff.data() + len);
	if(protocolName == IEC_103BAOXINNET_NW)
	{
		mText.append(CharToHexStr(buff.data() + len) + "\t" + eventTypeToText_nw(eventType) + "\r\n");
	}
	else
	{
		mText.append(CharToHexStr(buff.data() + len) + "\t" + eventTypeToText(eventType) + "\r\n");
	}
	len++;

	dtBegin = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	dtEnd = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
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

