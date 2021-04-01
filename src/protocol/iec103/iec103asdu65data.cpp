#include "iec103asdu65data.h"

IEC103Asdu65Data::IEC103Asdu65Data(const MyConfig& Config): IEC103AsduData(Config)
{
	rcc = 0;
}

IEC103Asdu65Data::~IEC103Asdu65Data()
{

}

bool IEC103Asdu65Data::handle(const QByteArray& buff)
{
	rcc = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + rcsToText_iec103(rcc) + "   " + seToText(rcc) + "   " + actToText(rcc) + "   " + quToText_iec103(rcc) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


