﻿#include "iec101asdu3data.h"

IEC101Asdu3Data::IEC101Asdu3Data(const MyConfig& Config): IEC101AsduData(Config)
{
	diq = 0;
}

IEC101Asdu3Data::~IEC101Asdu3Data()
{

}

bool IEC101Asdu3Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	diq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dpiToText(diq) + "   " + ivToText(diq) + "   " + ntToText(diq) + "   " + sbToText(diq) + "   " + blToText(diq) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

