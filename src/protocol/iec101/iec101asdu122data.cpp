﻿#include "iec101asdu122data.h"

IEC101Asdu122Data::IEC101Asdu122Data(const MyConfig& Config): IEC101AsduData(Config)
{
	nof = 0;
	nos = 0;
	scq = 0;
}

IEC101Asdu122Data::~IEC101Asdu122Data()
{

}

bool IEC101Asdu122Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");

	nof = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t文件名称NOF: " + QString::number(nof) + "\r\n");
	mLen += 2;

	nos = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t节名称NOS: " + QString::number(nos) + "\r\n");
	mLen++;

	scq = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + scqToText_iec101(scq) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

