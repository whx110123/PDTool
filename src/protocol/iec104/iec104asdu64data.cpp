﻿#include "iec104asdu64data.h"

IEC104Asdu64Data::IEC104Asdu64Data(const MyConfig& Config): IEC101Asdu51Data(Config)
{

}

IEC104Asdu64Data::~IEC104Asdu64Data()
{

}

bool IEC104Asdu64Data::handle(const QByteArray& buff)
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

	datetime = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

