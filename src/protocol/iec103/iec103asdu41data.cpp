#include "iec103asdu41data.h"

IEC103Asdu41Data::IEC103Asdu41Data(const MyConfig& Config): IEC103Asdu40Data(Config)
{

}

IEC103Asdu41Data::~IEC103Asdu41Data()
{

}

bool IEC103Asdu41Data::handle(const QByteArray& buff)
{
	siq = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + spiToText(siq) + "   " + ivToText(siq) + "   " + ntToText(siq) + "   " + sbToText(siq) + "   " + blToText(siq) + "\r\n");
	mLen++;

	datetime = charToDateTime(buff.data() + mLen, 4, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 4));
	mLen += 4;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

