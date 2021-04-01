#include "iec101asdu4data.h"

IEC101Asdu4Data::IEC101Asdu4Data(const MyConfig& Config): IEC101Asdu3Data(Config)
{

}

IEC101Asdu4Data::~IEC101Asdu4Data()
{

}

bool IEC101Asdu4Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	diq = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + dpiToText(diq) + "   " + ivToText(diq) + "   " + ntToText(diq) + "   " + sbToText(diq) + "   " + blToText(diq) + "\r\n");
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

