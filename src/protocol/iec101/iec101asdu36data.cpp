﻿#include "iec101asdu36data.h"

IEC101Asdu36Data::IEC101Asdu36Data()
{

}

IEC101Asdu36Data::~IEC101Asdu36Data()
{

}

bool IEC101Asdu36Data::handle(const QByteArray& buff)
{
	mText.append("\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");
	floatdata = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");
	len += 4;

	qds = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	len++;

	datetime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

