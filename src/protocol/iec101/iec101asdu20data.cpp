﻿#include "iec101asdu20data.h"

IEC101Asdu20Data::IEC101Asdu20Data(const MyConfig& Config): IEC101AsduData(Config)
{
	yx16 = 0;
	yx16flag = 0;
	qds = 0;
}

IEC101Asdu20Data::~IEC101Asdu20Data()
{

}

bool IEC101Asdu20Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	yx16 = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t" + yx16ToText() + "\r\n");
	len += 2;

	yx16flag = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t" + yx16FlagToText() + "\r\n");
	len += 2;

	qds = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}


QString IEC101Asdu20Data::yx16ToText()
{
	QString text = "16个单点遥信状态";
	for(int i = 0; i < 16; i++)
	{
		text.append("\r\n\t");
		text.append((yx16 >> i) & 0x01 ? "1 合位" : "0 分位");
		text.append(" 对应信息体地址:" + QString::number(infaddr + i));
	}
	return text;
}

QString IEC101Asdu20Data::yx16FlagToText()
{
	QString text = "16个单点遥信与上次查询的变化状态";
	for(int i = 0; i < 16; i++)
	{
		text.append("\r\n\t");
		text.append((yx16flag >> i) & 0x01 ? "1  有改变" : "0  无改变");
		text.append(" 对应信息体地址:" + QString::number(infaddr + i));
	}
	return text;
}
