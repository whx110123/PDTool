#include "iec103asdu40data.h"

IEC103Asdu40Data::IEC103Asdu40Data(const MyConfig& Config): IEC103AsduData(Config)
{
	siq = 0;
}

IEC103Asdu40Data::~IEC103Asdu40Data()
{

}

bool IEC103Asdu40Data::handle(const QByteArray& buff)
{
	siq = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + spiToText(siq) + "   " + ivToText(siq) + "   " + ntToText(siq) + "   " + sbToText(siq) + "   " + blToText(siq) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


