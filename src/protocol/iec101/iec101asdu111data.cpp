﻿#include "iec101asdu111data.h"

IEC101Asdu111Data::IEC101Asdu111Data()
{

}

IEC101Asdu111Data::~IEC101Asdu111Data()
{

}

bool IEC101Asdu111Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	shortdata = charToint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t标度化值:" + QString::number(shortdata) + "\r\n");
	len += 2;

	qpm = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + qpmToText(qpm) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

