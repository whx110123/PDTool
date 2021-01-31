﻿#include "iec101asdu113data.h"

IEC101Asdu113Data::IEC101Asdu113Data(const MyConfig& Config): IEC101AsduData(Config)
{
	qpa = 0;
}

IEC101Asdu113Data::~IEC101Asdu113Data()
{

}

bool IEC101Asdu113Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");

	qpa = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + qpaToText(qpa) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

