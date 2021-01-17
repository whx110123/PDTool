#include "iec101apci.h"

IEC101Code::IEC101Code()
{
	mcode = 0;
}

IEC101Code::~IEC101Code()
{

}

bool IEC101Code::init(const QByteArray& buff)
{
	setDefault(buff);
	mcode = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + prmToText(mcode) + "\r\n\t");
	if(mcode & 0x40)
	{
		mText.append(fcbToText(mcode) + "\r\n\t" + fcvToText(mcode) + "\r\n\t" + cw1ToText(mcode) + "\r\n");
	}
	else
	{
		mText.append(acdToText(mcode) + "\r\n\t" + dfcToText(mcode) + "\r\n\t" + cw2ToText(mcode) + "\r\n");
	}
	len++;
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Code::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
IEC101Apci::IEC101Apci()
{
	flag = 0;
	length = 0;
	addr = 0;

	mAddrLen = mConfig.addrLen;
	mLengthType = mConfig.lengthType;
}

IEC101Apci::~IEC101Apci()
{

}

bool IEC101Apci::init(const QByteArray& buff)
{
	setDefault(buff);

	if(buff.count() < 2 + mAddrLen)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度不足");
		return false;
	}
	flag = *(buff.data() + len);

	if(flag == 0x68)
	{

		mText.append(CharToHexStr(buff.data() + len) + "\t启动字符:0x68\r\n");
		len++;

		int lengthlen = stringToInt(mLengthType);
		if(lengthlen == 0)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未知的长度域类型");
			return false;
		}
		if(mLengthType == IEC_DOUBLESAME)
		{
			length = *(uchar *)(buff.data() + len);
			mText.append(CharToHexStr(buff.data() + len) + "\t长度域1:" + QString::number(length) + "\r\n");
			len++;

			uchar length2 = *(buff.data() + len);
			mText.append(CharToHexStr(buff.data() + len) + "\t长度域2:" + QString::number(length2) + "\r\n");
			len++;

			if(length != length2)
			{
				error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度域不同");
				return false;
			}
		}
		else if(mLengthType == IEC_SINGLE || mLengthType == IEC_DOUBLEDIFF)
		{
			length = charTouint(buff.data() + len, lengthlen);
			mText.append(CharToHexStr(buff.data() + len, lengthlen) + "\t长度域:" + QString::number(length) + "\r\n");
			len += lengthlen;
		}

		if(buff.count() < 3 + lengthlen + mAddrLen)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度不足");
			return false;
		}

		uchar flag2 = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\t启动字符:0x68\r\n");
		len++;
		if(flag2 != flag)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！第二个标志位错误");
			return false;
		}

	}
	else if(flag == 0x10)
	{
		mText.append(CharToHexStr(buff.data() + len) + "\t启动字符:0x10\r\n");
		len++;
		length = 1 + mAddrLen;
	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + len) + "\t出错！启动字符不是0x68");
		return false;
	}

	if(!code.init(buff.mid(len, 1)))
	{
		return false;
	}
	masterState = code.masterState;
	slaveState = code.slaveState;
	mText.append(code.showToText());
	len++;

	addr = charTouint(buff.data() + len, mAddrLen);
	mText.append(CharToHexStr(buff.data() + len, mAddrLen) + "\t地址域:" + QString::number(addr) + "\r\n");
	len += mAddrLen;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;

}


bool IEC101Apci::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
