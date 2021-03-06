﻿#include "iec101asdu102data.h"

IEC101Asdu102Data::IEC101Asdu102Data(const MyConfig& Config): IEC101AsduData(Config)
{

}

IEC101Asdu102Data::~IEC101Asdu102Data()
{

}

bool IEC101Asdu102Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

