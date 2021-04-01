#include "iec101asdu110data.h"

IEC101Asdu110Data::IEC101Asdu110Data(const MyConfig& Config): IEC101AsduData(Config)
{
	shortdata = 0;
	qpm = 0;
}

IEC101Asdu110Data::~IEC101Asdu110Data()
{

}

bool IEC101Asdu110Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	shortdata = charToint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");
	mLen += 2;

	qpm = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + qpmToText(qpm) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

