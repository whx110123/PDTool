#include "iec103asdu50data.h"

IEC103Asdu50Data::IEC103Asdu50Data(const MyConfig& Config): IEC103AsduData(Config)
{
	shortdata = 0;
	qds = 0;
}

IEC103Asdu50Data::~IEC103Asdu50Data()
{

}

bool IEC103Asdu50Data::handle(const QByteArray& buff)
{
	shortdata = charToshortwithQ(buff.data() + mLen);
	qds = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t带品质描述词的被测值(bit4-16):" + QString::number(shortdata) + "   对应INF:" + QString::number(inf) + "\r\n\t" + ovToText(qds) + "   " + erToText(qds) + "\r\n");
	mLen += 2;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


