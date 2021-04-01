#include "iec104.h"

IEC104::IEC104(const MyConfig& Config): MyBase(Config), apci(Config), asdu(Config)
{
	mMasterState = STATE_INIT;
}

IEC104::~IEC104()
{

}

bool IEC104::init(const QByteArray& buff)
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


QString IEC104::showToText()
{
	QString text(mText);
	if(mLen > 5)
	{
		text.append(apci.showToText());
	}
	if(mLen > 6 && apci.control.type == ITYPE)
	{
		text.append(asdu.showToText());
	}
	return text;
}

bool IEC104::createData(MyData& proData)
{
	if(apci.createData(proData))
	{
		if(apci.control.type == ITYPE)
		{
			if(asdu.createData(proData))
			{
				return true;
			}
		}
		return true;
	}
	mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;

//	config.data.clear();
//	if(config.isMaster)
//	{
//		switch(config.mMasterState)
//		{
//		case STATE_INIT:
//		case STATE_TESTACT:
//		case STATE_TESTCONFIRM:
//			config.controltype = UTYPE;
//			config.asdutype = 0;
//			break;
//		case STATE_NORMAL:
//			config.controltype = STYPE;
//			config.asdutype = 0;
//			break;
//		case STATE_CALLALL:
//			config.controltype = ITYPE;
//			config.asdutype = 0x64;
//			config.vsq = 1;
//			config.cot = 0x06;
//			break;
//		case STATE_SETTIME:
//			config.controltype = ITYPE;
//			config.asdutype = 0x67;
//			config.vsq = 1;
//			config.cot = 0x06;
//			break;
//		case STATE_USER:
//			config.controltype = ITYPE;
//			break;
//		case STATE_HOTKEY:
//			break;
//		default:
//			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的主站状态");
//			return false;
//			break;
//		}
//	}
//	else
//	{
//		switch(config.mSlaveState)
//		{
//		case STATE_NODATA:
//			return true;
//			break;
//		case STATE_INIT:
//		case STATE_TESTACT:
//		case STATE_TESTCONFIRM:
//		case STATE_NORMAL:
//		case STATE_CALLALL:
//			config.controltype = UTYPE;
//			config.asdutype = 0;
//			break;
//		case STATE_USER:
//			config.controltype = ITYPE;
//			config.asdutype = 0;
//			break;
//		case STATE_HOTKEY:
//			break;
//		default:
//			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的子站状态");
//			return false;
//			break;
//		}
//	}

//	if(!apci.createData(config))
//	{
//		return false;
//	}
//	if(config.asdutype > 0)
//	{
//		if(!asdu.createData(config))
//		{
//			return false;
//		}
//	}
//	if(config.data.size() < 5)
//	{
//		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文长度不足5");
//		return false;
//	}
//	if(config.mMasterState == STATE_USER || config.mSlaveState == STATE_USER)
//	{
//		config.data.append(config.userdata);
//		config.userdata.clear();
//	}
//	uchar len = config.data.size() - 2;
//	config.data.replace(1, 1, (char *)&len, 1);
//	return true;
}


