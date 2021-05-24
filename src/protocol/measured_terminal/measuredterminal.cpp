#include "measuredterminal.h"

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

	int LENGTH_LEN = stringToInt(mConfig.lengthType);	//长度域字节数
	int APCI_LEN = 10 + LENGTH_LEN;
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
	mLen += apci.mLen;

	if(mLen != APCI_LEN)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}
	int APDU_LEN = APCI_LEN - 8 + apci.length + 2;		//APDU总字节数
	if(APDU_LEN > buff.count())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}

	asdu.flag = 0;
	if(apci.code.mcode & 0x40)
	{
		asdu.flag |= ISMASTER;
	}
	if(!asdu.init(buff.mid(mLen, APDU_LEN - APCI_LEN - 2)))
	{
		mText.append(asdu.showToText());
		return false;
	}
	mText.append(asdu.showToText());
	mLen += asdu.mLen;


	uchar crctmp = crcsum(buff.data(), APCI_LEN - 8, APDU_LEN - 3);
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


