﻿#include "iec103asdu221data.h"

IEC103Asdu221Data::IEC103Asdu221Data(const MyConfig& Config): IEC103AsduData(Config)
{
	fnam = 0;
	snam = 0;
	scq = 0;
}

IEC103Asdu221Data::~IEC103Asdu221Data()
{

}

bool IEC103Asdu221Data::handle(const QByteArray& buff)
{
	fnam = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t文件名称FNAM: " + QString::number(fnam) + "\r\n");
	mLen += 2;

	snam = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t节名称SNAM: " + QString::number(snam) + "\r\n");
	mLen++;

	scq = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + scqToText_iec103(scq) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

