#include "iec101asdu63data.h"

IEC101Asdu63Data::IEC101Asdu63Data(const MyConfig& Config): IEC101Asdu50Data(Config)
{

}

IEC101Asdu63Data::~IEC101Asdu63Data()
{

}

bool IEC101Asdu63Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	floatdata = charTofloat(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");
	mLen += 4;

	qos = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + qosToText(qos) + "\r\n");
	mLen++;

	datetime = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu63Data::createData(MyData& proData)
{
//	config.data += uintToBa(config.infaddr, mConfig.infaddrlen);
//	config.data += config.infdata;
	return true;
}
