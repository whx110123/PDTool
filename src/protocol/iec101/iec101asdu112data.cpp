#include "iec101asdu112data.h"

IEC101Asdu112Data::IEC101Asdu112Data(const MyConfig& Config): IEC101AsduData(Config)
{
	floatdata = 0;
	qpm = 0;
}

IEC101Asdu112Data::~IEC101Asdu112Data()
{

}

bool IEC101Asdu112Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	floatdata = charTofloat(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");
	mLen += 4;

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

