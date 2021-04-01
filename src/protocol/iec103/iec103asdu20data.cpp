#include "iec103asdu20data.h"

IEC103Asdu20Data::IEC103Asdu20Data(const MyConfig& Config): IEC103AsduData(Config)
{
	dco = 0;
}

IEC103Asdu20Data::~IEC103Asdu20Data()
{

}

bool IEC103Asdu20Data::handle(const QByteArray& buff)
{
	dco = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + dcsToText(dco) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

