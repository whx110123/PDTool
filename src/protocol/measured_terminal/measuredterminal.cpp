﻿#include "measuredterminal.h"

MeasuredTerminal::MeasuredTerminal(const MyConfig& Config): MyBase(Config), apci(Config), asdu(Config)
{
	crc = 0;
	end = 0;
}

MeasuredTerminal::~MeasuredTerminal()
{

}

bool MeasuredTerminal::init(const QByteArray& buff)
{
	setDefault(buff);

	if(buff.count() < 13)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度不足");
		return false;
	}
	int LENGTH_LEN = stringToInt(mConfig.lengthType);	//长度域字节数
	int APCI_LEN = 10 + LENGTH_LEN;

	if(!apci.init(buff.left(APCI_LEN)))
	{
		mRecvData = buff.left(APCI_LEN);
		return false;
	}
	len = APCI_LEN - 8 + apci.length + 2;

	if(len > buff.count())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}
	mRecvData = buff.left(len);

	asdu.flag = 0;
	if(apci.code.mcode & 0x40)
	{
		asdu.flag |= ISMASTER;
	}
	if(!asdu.init(buff.mid(APCI_LEN, len - APCI_LEN - 2)))
	{
		return false;
	}
	mMasterState = asdu.mMasterState;
	mSlaveState = asdu.mSlaveState;


	uchar crctmp = crcsum(buff.data(), APCI_LEN - 8, len - 3);
	crc = *(buff.data() + len - 2);
	if(crc != crctmp)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！校验错误");
//		return false;
	}

	end = *(buff.data() + len - 1);
	if(end != 0x16)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文结束位错误");
		return false;
	}
	if(len > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString MeasuredTerminal::showToText()
{
	QString text;
	text.append(apci.showToText());
	text.append(asdu.showToText());
	text.append(CharToHexStr(crc) + "\t校验和\r\n");
	text.append(CharToHexStr(end) + "\t结束字符\r\n");
	return text;
}

