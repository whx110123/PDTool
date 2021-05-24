#include "iec103com.h"

IEC103COM::IEC103COM(const MyConfig& Config): MyBase(Config), apci(Config), asdu(Config)
{
	crc = 0;
	end = 0;
}

IEC103COM::~IEC103COM()
{

}

bool IEC103COM::init(const QByteArray& buff)
{
	setDefault(buff);

	if(mConfig.addrLen + 4 > buff.length())
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
	if(APCI_LEN > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！报文总长不满%1个字节，条件不满足，因此报文有问题").arg(APCI_LEN));
		return false;
	}
	if(!apci.init(buff.mid(mLen, APCI_LEN)))
	{
		mText.append(apci.showToText());
		return false;
	}
	mText.append(apci.showToText());
	mLen = apci.mLen;

	if(mLen != APCI_LEN)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}
	int APDU_LEN = APCI_LEN - 2 + apci.length + 2;		//APDU总字节数
	if(APDU_LEN > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(APDU_LEN).arg(buff.length()));
		return false;
	}

	if(apci.flag == 0x68)
	{
		if(!asdu.init(buff.mid(mLen, APDU_LEN - APCI_LEN - 2)))
		{
			mText.append(asdu.showToText());
			return false;
		}
		mText.append(asdu.showToText());
		mLen += asdu.mLen;
	}

	uchar crctmp = crcsum(buff.data(), APCI_LEN - 2, APDU_LEN - 3);
	crc = *(buff.data() + mLen);
	mText.append(CharToHexStr(crc) + "\t校验和\r\n");
	if(crc != crctmp)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！校验错误");
		return false;
	}
	mLen++;

	end = *(buff.data() + mLen);
	mText.append(CharToHexStr(end) + "\t结束字符\r\n");
	if(end != 0x16)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文结束位错误");
		return false;
	}
	mLen++;

	if(mLen != APDU_LEN)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}

	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}


