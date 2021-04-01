#include "iec103asdu43data.h"

IEC103Asdu43Data::IEC103Asdu43Data(const MyConfig& Config): IEC103Asdu42Data(Config)
{

}

IEC103Asdu43Data::~IEC103Asdu43Data()
{

}

bool IEC103Asdu43Data::handle(const QByteArray& buff)
{
	diq = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + dpiToText(diq) + "   " + ivToText(diq) + "   " + ntToText(diq) + "   " + sbToText(diq) + "   " + blToText(diq) + "\r\n");
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


