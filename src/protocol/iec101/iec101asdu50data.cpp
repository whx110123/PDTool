#include "iec101asdu50data.h"

IEC101Asdu50Data::IEC101Asdu50Data(const MyConfig& Config): IEC101AsduData(Config)
{
	floatdata = 0;
	qos = 0;
}

IEC101Asdu50Data::~IEC101Asdu50Data()
{

}

bool IEC101Asdu50Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	floatdata = charTofloat(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");
	mLen += 4;

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

bool IEC101Asdu50Data::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	if(tmp.sqFlag == SQ_INF)
	{
		tmp.data += uintToBa(infaddr, mConfig.infaddrlen);
	}
	tmp.data += floatToBa(floatdata);
	tmp.data += qos;

	if(proData.reverse)
	{
		proData = tmp + proData;
	}
	else
	{
		proData = proData + tmp;
	}
	mSendData = proData.data;
	return true;
}
