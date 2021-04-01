#include "iec103netwiscom.h"

IEC103NetWiscom::IEC103NetWiscom(const MyConfig& Config): MyBase(Config), apci(Config), asdu(Config)
{
	mMasterState = STATE_INIT;
}

IEC103NetWiscom::~IEC103NetWiscom()
{

}

bool IEC103NetWiscom::init(const QByteArray& buff)
{
	setDefault(buff);

	int LENGTH_LEN = stringToInt(mConfig.lengthType);	//长度域字节数
	int APCI_LEN = LENGTH_LEN + 13;					//APCI总字节数

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
	len = apci.length + LENGTH_LEN + 1;
	mMasterState = apci.mMasterState;
	mSlaveState = apci.mSlaveState;
	if(len > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	mRecvData = buff.left(len);

	if(apci.control.type == ITYPE && buff.count() <= APCI_LEN)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！I帧报文无ASDU数据");
		return false;
	}
	else if(apci.control.type == UTYPE || apci.control.type == STYPE)
	{
		if(len != APCI_LEN)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
			return false;
		}
		else
		{
			if(len > buff.length())
			{
				mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
				return false;
			}
			return true;
		}
	}

	if(!asdu.init(buff.mid(APCI_LEN, len - APCI_LEN)))
	{
		return false;
	}
	mMasterState = asdu.mMasterState;
	mSlaveState = asdu.mSlaveState;
	if(len > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;

}


QString IEC103NetWiscom::showToText()
{
	QString text(mText);
	int LENGTH_LEN = stringToInt(mConfig.lengthType);	//长度域字节数
	if(len > LENGTH_LEN + 12)
	{
		text.append(apci.showToText());
	}
	if(len > LENGTH_LEN + 13 && apci.control.type == ITYPE)
	{
		text.append(asdu.showToText());
	}
	return text;
}

