﻿#include "iec103netbaoxin.h"

IEC103NetBaoXin::IEC103NetBaoXin(const MyConfig& Config): MyBase(Config), apci(Config), asdu(Config)
{
	mMasterState = STATE_INIT;
}

IEC103NetBaoXin::~IEC103NetBaoXin()
{

}

bool IEC103NetBaoXin::init(const QByteArray& buff)
{
	setDefault(buff);

	int LENGTH_LEN = stringToInt(mConfig.lengthType);	//长度域字节数
	int APCI_LEN = LENGTH_LEN + 5;					//APCI总字节数

	if(buff.count() < APCI_LEN)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！报文总长不满%1个字节，条件不满足，因此报文有问题\r\n").arg(APCI_LEN));
		return false;
	}

	if(!apci.init(buff.left(APCI_LEN)))
	{
		mRecvData = buff.left(APCI_LEN);
		return false;
	}
	mLen = apci.length + LENGTH_LEN + 1;
	mMasterState = apci.mMasterState;
	mSlaveState = apci.mSlaveState;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData = buff.left(mLen);

	if(apci.control.type == ITYPE && buff.count() <= APCI_LEN)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！I帧报文无ASDU数据");
		return false;
	}
	else if(apci.control.type == UTYPE || apci.control.type == STYPE)
	{
		if(mLen != APCI_LEN)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
			return false;
		}
		else
		{
			if(mLen > buff.length())
			{
				mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
				return false;
			}
			return true;
		}
	}

	if(!asdu.init(buff.mid(APCI_LEN, mLen - APCI_LEN)))
	{
		return false;
	}
	mMasterState = asdu.mMasterState;
	mSlaveState = asdu.mSlaveState;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103NetBaoXin::showToText()
{
	QString text(mText);
	if(mLen > 6)
	{
		text.append(apci.showToText());
	}
	if(mLen > 7 && apci.control.type == ITYPE)
	{
		text.append(asdu.showToText());
	}
	return text;
}

