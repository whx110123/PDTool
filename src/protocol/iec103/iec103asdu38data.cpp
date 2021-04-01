#include "iec103asdu38data.h"

IEC103Asdu38Data::IEC103Asdu38Data(const MyConfig& Config): IEC103AsduData(Config)
{
	vti = 0;
	qds = 0;
}

IEC103Asdu38Data::~IEC103Asdu38Data()
{

}

bool IEC103Asdu38Data::handle(const QByteArray& buff)
{
	vti = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + vtiToText_iec103(vti)  + "\r\n");
	mLen++;

	qds = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


