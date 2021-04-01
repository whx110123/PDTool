#include "iec101asdu127data.h"

IEC101Asdu127Data::IEC101Asdu127Data(const MyConfig& Config): IEC101AsduData(Config)
{
	nof = 0;
}

IEC101Asdu127Data::~IEC101Asdu127Data()
{

}

bool IEC101Asdu127Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");

	nof = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t文件名NOF: " + QString::number(nof) + "\r\n");
	mLen += 2;

	datetime1 = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

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

