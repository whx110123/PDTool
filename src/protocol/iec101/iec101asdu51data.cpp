﻿#include "iec101asdu51data.h"

IEC101Asdu51Data::IEC101Asdu51Data(const MyConfig& Config): IEC101AsduData(Config)
{
	uintdata = 0;
}

IEC101Asdu51Data::~IEC101Asdu51Data()
{

}

bool IEC101Asdu51Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	uintdata = charTouint(buff.data() + mLen, 4);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t32比特串:"  + "\r\n");
	for(int i = 0; i < 32; i++)
	{
		mText.append(QString("\tbit%1状态: ").arg(i + 1));
		if((uintdata >> i) & 1)
		{
			mText.append("合");
		}
		else
		{
			mText.append("分");
		}
		mText.append("\r\n");
	}
	mLen += 4;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu51Data::createData(MyData& proData)
{
//	config.data += uintToBa(config.infaddr, mConfig.infaddrlen);
//	config.data += config.infdata;
	return true;
}
