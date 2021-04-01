#include "iec103asdu17data.h"

IEC103Asdu17Data::IEC103Asdu17Data(const MyConfig& Config): IEC103Asdu15Data(Config)
{

}

IEC103Asdu17Data::~IEC103Asdu17Data()
{

}

bool IEC103Asdu17Data::handle(const QByteArray& buff)
{
	if(mConfig.protocolName == IEC_103BAOXINNET_NW)
	{
		rii = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
		mLen++;
	}

	eventType = *(buff.data() + mLen);
	if(mConfig.protocolName == IEC_103BAOXINNET_NW)
	{
		mText.append(CharToHexStr(buff.data() + mLen) + "\t" + eventTypeToText_nw(eventType) + "\r\n");
	}
	else
	{
		mText.append(CharToHexStr(buff.data() + mLen) + "\t" + eventTypeToText(eventType) + "\r\n");
	}
	mLen++;

	dtBegin = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	dtEnd = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

