#include "iec101asdu39data.h"

IEC101Asdu39Data::IEC101Asdu39Data(const MyConfig& Config): IEC101Asdu18Data(Config)
{

}

IEC101Asdu39Data::~IEC101Asdu39Data()
{

}

bool IEC101Asdu39Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	spe = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t继电保护设备的启动事件SPE:" + gsToText(spe) + "   " + sl1ToText(spe) + "   " + sl2ToText(spe) + "   " + sl3ToText(spe) + "   " + sieToText(spe) + "   " + srdToText(spe) + "\r\n");
	mLen++;

	qdp = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t继电保护设备事件的品质描述词QDP:"  + ivToText(qdp) + "   " + ntToText(qdp) + "   " + sbToText(qdp) + "   " + blToText(qdp) + "   " + eiToText(qdp) + "\r\n");
	mLen++;

	datetime1 = charToDateTime(buff.data() + mLen, 2, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 2));
	mLen += 2;

	datetime2 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
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
