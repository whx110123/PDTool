#include "iec103netbaoxin.h"

IEC103NetBaoXin::IEC103NetBaoXin()
{
	masterState = STATE_INIT;

	mLengthType = mConfig.lengthType;
}

IEC103NetBaoXin::~IEC103NetBaoXin()
{

}

bool IEC103NetBaoXin::init(const QByteArray& buff)
{
	setDefault(buff);

	int LENGTH_LEN = stringToInt(mLengthType);	//长度域字节数
	int APCI_LEN = LENGTH_LEN + 5;					//APCI总字节数

	if(buff.count() < APCI_LEN)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！报文总长不满%1个字节，条件不满足，因此报文有问题\r\n").arg(APCI_LEN));
		return false;
	}

	if(!apci.init(buff.left(APCI_LEN)))
	{
		mRecvData = buff.left(APCI_LEN);
		return false;
	}
	len = apci.length + LENGTH_LEN + 1;
	masterState = apci.masterState;
	slaveState = apci.slaveState;
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	mRecvData = buff.left(len);

	if(apci.control.type == ITYPE && buff.count() <= APCI_LEN)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！I帧报文无ASDU数据");
		return false;
	}
	else if(apci.control.type == UTYPE || apci.control.type == STYPE)
	{
		if(len != APCI_LEN)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
			return false;
		}
		else
		{
			if(len > buff.length())
			{
				error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
				return false;
			}
			return true;
		}
	}

	if(!asdu.init(buff.mid(APCI_LEN, len - APCI_LEN)))
	{
		return false;
	}
	masterState = asdu.masterState;
	slaveState = asdu.slaveState;
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103NetBaoXin::showToText()
{
	QString text(mText);
	if(len > 6)
	{
		text.append(apci.showToText());
	}
	if(len > 7 && apci.control.type == ITYPE)
	{
		text.append(asdu.showToText());
	}
	return text;
}

bool IEC103NetBaoXin::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
