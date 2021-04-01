#include "iec101asdu47data.h"

IEC101Asdu47Data::IEC101Asdu47Data(const MyConfig& Config): IEC101AsduData(Config)
{
	rco = 0;
}

IEC101Asdu47Data::~IEC101Asdu47Data()
{

}

bool IEC101Asdu47Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	rco = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + rcsToText_iec101(rco) + "   " + seToText(rco) + "   " + quToText_iec101(rco) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu47Data::createData(MyData& proData)
{
//	config.data += uintToBa(config.infaddr, mConfig.infaddrlen);
//	config.data += config.infdata;
	return true;
}
