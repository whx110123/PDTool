#include "iec103asdu67data.h"

IEC103Asdu67Data::IEC103Asdu67Data(const MyConfig& Config): IEC103AsduData(Config)
{
	ccc = 0;
}

IEC103Asdu67Data::~IEC103Asdu67Data()
{

}

bool IEC103Asdu67Data::handle(const QByteArray& buff)
{
	ccc = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + ccsToText(ccc) + "   " + seToText(ccc) + "   " + actToText(ccc) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


