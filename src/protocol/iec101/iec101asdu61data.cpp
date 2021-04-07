#include "iec101asdu61data.h"

IEC101Asdu61Data::IEC101Asdu61Data(const MyConfig& Config): IEC101Asdu48Data(Config)
{

}

IEC101Asdu61Data::~IEC101Asdu61Data()
{

}

bool IEC101Asdu61Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	shortdata = charToint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");
	mLen += 2;

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

