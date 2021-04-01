#include "iec101asdu14data.h"

IEC101Asdu14Data::IEC101Asdu14Data(const MyConfig& Config): IEC101Asdu13Data(Config)
{

}

IEC101Asdu14Data::~IEC101Asdu14Data()
{

}

bool IEC101Asdu14Data::handle(const QByteArray& buff)
{
	mText.append("\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");
	floatdata = charTofloat(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");
	mLen += 4;

	qds = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	mLen++;

	datetime = charToDateTime(buff.data() + mLen, 3, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 3));
	mLen += 3;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

