#include "iec104.h"

IEC104::IEC104(const MyConfig& Config): MyBase(Config), apci(Config), asdu(Config)
{

}

IEC104::~IEC104()
{

}

bool IEC104::init(const QByteArray& buff)
{
	setDefault(buff);

	int LENGTH_LEN = stringToInt(mConfig.lengthType);	//长度域字节数
	int APCI_LEN = LENGTH_LEN + 5;						//APCI总字节数

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

	int APDU_LEN = apci.length + LENGTH_LEN + 1;		//APDU总字节数
	if(APDU_LEN > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(APDU_LEN).arg(buff.length()));
		return false;
	}

	if(apci.control.type == IEC104Control::ITYPE)
	{
		if(!asdu.init(buff.mid(mLen, APDU_LEN - APCI_LEN)))
		{
			mText.append(asdu.showToText());
			return false;
		}
		mText.append(asdu.showToText());
		mLen += asdu.mLen;
	}

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

bool IEC104::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	if(apci.control.type == IEC104Control::ITYPE)
	{
		tmp.reverse = false;
		if(!asdu.createData(tmp))
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
			return false;
		}
	}
	tmp.reverse = true;
	if(!apci.createData(tmp))
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
		return false;
	}

	if(proData.reverse)
	{
		proData = tmp + proData;
	}
	else
	{
		proData = proData + tmp;
	}
	mSendData = proData.data;
	return true;
}


