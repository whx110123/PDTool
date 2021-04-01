#include "iec101asdu121data.h"

IEC101Asdu121Data::IEC101Asdu121Data(const MyConfig& Config): IEC101AsduData(Config)
{
	nof = 0;
	nos = 0;
	lof = 0;
	srq = 0;
}

IEC101Asdu121Data::~IEC101Asdu121Data()
{

}

bool IEC101Asdu121Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");

	nof = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t文件名称NOF: " + QString::number(nof) + "\r\n");
	mLen += 2;

	nos = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t节名称NOS: " + QString::number(nos) + "\r\n");
	mLen++;

	lof = charTouint(buff.data() + mLen, 3);
	mText.append(CharToHexStr(buff.data() + mLen, 3) + "\t节长度LOF: " + QString::number(lof) + "\r\n");
	mLen += 3;

	srq = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + srqToText(srq) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


