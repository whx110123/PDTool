#include "iec101asdu49data.h"

IEC101Asdu49Data::IEC101Asdu49Data(const MyConfig& Config): IEC101AsduData(Config)
{
	shortdata = 0;
	qos = 0;
}

IEC101Asdu49Data::~IEC101Asdu49Data()
{

}

bool IEC101Asdu49Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	shortdata = charToint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t标度化值:" + QString::number(shortdata) + "\r\n");
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

bool IEC101Asdu49Data::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	if(tmp.sqFlag == SQ_INF)
	{
		tmp.data += uintToBa(infaddr, mConfig.infaddrlen);
	}
	tmp.data += intToBa(shortdata, 2);
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
