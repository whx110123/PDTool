#include "iec101asdu35data.h"

IEC101Asdu35Data::IEC101Asdu35Data(const MyConfig& Config): IEC101Asdu12Data(Config)
{

}

IEC101Asdu35Data::~IEC101Asdu35Data()
{

}

bool IEC101Asdu35Data::handle(const QByteArray& buff)
{
	mText.append("\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");
	shortdata = charToint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t标度化值:" + QString::number(shortdata) + "\r\n");
	mLen += 2;

	qds = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
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

