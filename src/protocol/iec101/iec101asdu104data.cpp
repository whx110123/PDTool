﻿#include "iec101asdu104data.h"

IEC101Asdu104Data::IEC101Asdu104Data(const MyConfig& Config): IEC101AsduData(Config)
{
	ushortData = 0;
}

IEC101Asdu104Data::~IEC101Asdu104Data()
{

}

bool IEC101Asdu104Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	ushortData = charTouint(buff.data() + mLen, 2);
	if(ushortData != 0x55AA)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！固定测试字不是0x55AA"));
		return false;
	}
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t固定测试字FBP: 0x55AA\r\n");
	mLen += 2;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

