#include "iec101asdu2data.h"

IEC101Asdu2Data::IEC101Asdu2Data(const MyConfig& Config): IEC101Asdu1Data(Config)
{

}

IEC101Asdu2Data::~IEC101Asdu2Data()
{

}

bool IEC101Asdu2Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	siq = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + spiToText(siq) + "   " + ivToText(siq) + "   " + ntToText(siq) + "   " + sbToText(siq) + "   " + blToText(siq) + "\r\n");
	mLen++;

	datetime = charToDateTime(buff.data() + mLen, 3, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 3));
	mLen += 3;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}
