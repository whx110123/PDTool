#include "iec103asdu24data.h"

IEC103Asdu24Data::IEC103Asdu24Data(const MyConfig& Config): IEC103AsduData(Config)
{
	too = 0;
	tov = 0;
	fan = 0;
	acc = 0;
}

IEC103Asdu24Data::~IEC103Asdu24Data()
{

}

bool IEC103Asdu24Data::handle(const QByteArray& buff)
{
	too = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + tooToText(too) + "\r\n");
	mLen++;

	tov = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + tovToText(tov) + "\r\n");
	mLen++;

	fan = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	mLen += 2;

	acc = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + accToText(acc) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

