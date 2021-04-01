#include "iec103asdu66data.h"

IEC103Asdu66Data::IEC103Asdu66Data(const MyConfig& Config): IEC103AsduData(Config)
{
	shortdata = 0;
	qos = 0;
}

IEC103Asdu66Data::~IEC103Asdu66Data()
{

}

bool IEC103Asdu66Data::handle(const QByteArray& buff)
{
	shortdata = charToint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t设定值:" + QString::number(shortdata) + "\r\n");
	mLen += 2;

	qos = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + qosToText(qos) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


