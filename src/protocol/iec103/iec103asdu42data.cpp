﻿#include "iec103asdu42data.h"

IEC103Asdu42Data::IEC103Asdu42Data(const MyConfig& Config): IEC103AsduData(Config)
{
	diq = 0;
}

IEC103Asdu42Data::~IEC103Asdu42Data()
{

}


bool IEC103Asdu42Data::handle(const QByteArray& buff)
{
	diq = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + dpiToText(diq) + "   " + ivToText(diq) + "   " + ntToText(diq) + "   " + sbToText(diq) + "   " + blToText(diq) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}




