﻿#include "iec101asdu63data.h"

IEC101Asdu63Data::IEC101Asdu63Data(const MyConfig& Config): IEC101Asdu50Data(Config)
{

}

IEC101Asdu63Data::~IEC101Asdu63Data()
{

}

bool IEC101Asdu63Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	floatdata = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");
	len += 4;

	qos = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + qosToText(qos) + "\r\n");
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

bool IEC101Asdu63Data::createData(IECDataConfig& config)
{
	config.data += uintToBa(config.infaddr, mInfaddrlen);
	config.data += config.infdata;
	return true;
}
