﻿#include "iec101asdu5data.h"

IEC101Asdu5Data::IEC101Asdu5Data(const MyConfig& Config): IEC101AsduData(Config)
{
	vti = 0;
	qds = 0;
}

IEC101Asdu5Data::~IEC101Asdu5Data()
{

}

bool IEC101Asdu5Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	vti = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + vtiToText_iec101(vti)  + "\r\n");
	len++;

	qds = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

