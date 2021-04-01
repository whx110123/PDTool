#include "iec101asdu17data.h"

IEC101Asdu17Data::IEC101Asdu17Data(const MyConfig& Config): IEC101AsduData(Config)
{
	sep = 0;
}

IEC101Asdu17Data::~IEC101Asdu17Data()
{

}

bool IEC101Asdu17Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	sep = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t继电保护的单个事件SEP:" + esToText(sep) + "   " + ivToText(sep) + "   " + ntToText(sep) + "   " + sbToText(sep) + "   " + blToText(sep) + "   " + eiToText(sep) + "\r\n");
	mLen++;

	datetime1 = charToDateTime(buff.data() + mLen, 2, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 2));
	mLen += 2;

	datetime2 = charToDateTime(buff.data() + mLen, 3, BINARYTIME2A);
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

