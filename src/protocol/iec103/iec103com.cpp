#include "iec103com.h"

IEC103COM::IEC103COM(const MyConfig& Config): MyBase(Config), apci(Config), asdu(Config)
{
	mMasterState = STATE_INIT;
	crc = 0;
	end = 0;
}

IEC103COM::~IEC103COM()
{

}

bool IEC103COM::init(const QByteArray& buff)
{
	setDefault(buff);

	if(buff.count() < mConfig.addrLen + 4)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度不足");
		return false;
	}
	int LENGTH_LEN = stringToInt(mConfig.lengthType);	//长度域字节数
	int APCI_LEN = 0;
	if(*buff.data() == 0x68)
	{
		APCI_LEN = 3 + LENGTH_LEN + mConfig.addrLen;
	}
	else if(*buff.data() == 0x10)
	{
		APCI_LEN = 2 + mConfig.addrLen;
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文头错误");
		return false;
	}
	if(!apci.init(buff.left(APCI_LEN)))
	{
		mRecvData = buff.left(APCI_LEN);
		return false;
	}
	mLen = APCI_LEN + apci.length;
	mMasterState = apci.mMasterState;
	mSlaveState = apci.mSlaveState;
	if(mLen > buff.count())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}
	mRecvData = buff.left(mLen);

	if(apci.flag == 0x68 && buff.count() > APCI_LEN + 3)
	{
		if(!asdu.init(buff.mid(APCI_LEN, mLen - APCI_LEN - 2)))
		{
			return false;
		}
		mMasterState = asdu.mMasterState;
		mSlaveState = asdu.mSlaveState;
	}
	else if(apci.flag == 0x10)
	{
		if(mLen != APCI_LEN + 2)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
			return false;
		}
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}

	uchar crctmp = crcsum(buff.data(), APCI_LEN - 2, mLen - 3);
	crc = *(buff.data() + mLen - 2);
	if(crc != crctmp)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！校验错误");
		return false;
	}

	end = *(buff.data() + mLen - 1);
	if(end != 0x16)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文结束位错误");
		return false;
	}
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


QString IEC103COM::showToText()
{
	QString text;
	text.append(apci.showToText());
	if(apci.flag == 0x68)
	{
		text.append(asdu.showToText());
	}
	text.append(CharToHexStr(crc) + "\t校验和\r\n");
	text.append(CharToHexStr(end) + "\t结束字符\r\n");
	return text;
}


