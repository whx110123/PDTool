﻿#include "iec103asdu88data.h"

IEC103Asdu88Data::IEC103Asdu88Data(const MyConfig& Config): IEC103AsduData(Config)
{
	qcc = 0;
}

IEC103Asdu88Data::~IEC103Asdu88Data()
{

}

bool IEC103Asdu88Data::handle(const QByteArray& buff)
{
	qcc = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t计数量召唤命令限定词(QCC):\r\n\t" + rqtToText(qcc) + "\r\n\t" + frzToText(qcc) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

