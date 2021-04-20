#include "iec104asdu137data.h"

IEC104Asdu137Data::IEC104Asdu137Data(const MyConfig& Config): IEC101AsduData(Config)
{
	shortdata = 0;
	qos = 0;
}

IEC104Asdu137Data::~IEC104Asdu137Data()
{

}

bool IEC104Asdu137Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	shortdata = charToint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");
	mLen += 2;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen + 8 == buff.length())
	{
		qos = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t" + qosToText(qos) + "\r\n");
		mLen++;

		datetime = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		mText.append("-----------------------------------------------------------------------------------------------\r\n");
	}
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


