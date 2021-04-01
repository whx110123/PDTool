#include "iec101asdu6data.h"

IEC101Asdu6Data::IEC101Asdu6Data(const MyConfig& Config): IEC101Asdu5Data(Config)
{

}

IEC101Asdu6Data::~IEC101Asdu6Data()
{

}

bool IEC101Asdu6Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	vti = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + vtiToText_iec101(vti)  + "\r\n");
	mLen++;

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

