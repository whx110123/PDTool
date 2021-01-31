﻿#include "iec103asdu101data.h"

IEC103Asdu101Data::IEC103Asdu101Data(const MyConfig& Config): IEC103Asdu15Data(Config)
{
	gbk = QTextCodec::codecForName("GB18030");
}

IEC103Asdu101Data::~IEC103Asdu101Data()
{

}

bool IEC103Asdu101Data::handle(const QByteArray& buff)
{
	rii = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	len++;

	dtBegin = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	dtEnd = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	QByteArray ba(buff.data() + len, 100);
	fileName = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + len, 100) + "\t一般文件名称100个字节:   " + fileName + "\r\n");
	len += 100;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}
