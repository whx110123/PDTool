#include "iec101apci.h"

IEC101Code::IEC101Code(const MyConfig& Config): MyBase(Config)
{
	mcode = 0;
}

IEC101Code::~IEC101Code()
{

}

bool IEC101Code::init(const QByteArray& buff)
{
	setDefault(buff);
	mcode = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + prmToText(mcode) + "\r\n\t");
	if(mcode & 0x40)
	{
		mText.append(fcbToText(mcode) + "\r\n\t" + fcvToText(mcode) + "\r\n\t" + cw1ToText(mcode) + "\r\n");
	}
	else
	{
		mText.append(acdToText(mcode) + "\r\n\t" + dfcToText(mcode) + "\r\n\t" + cw2ToText(mcode) + "\r\n");
	}
	mLen++;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

IEC101Apci::IEC101Apci(const MyConfig& Config): MyBase(Config), code(Config)
{
	flag = 0;
	length = 0;
	addr = 0;
}

IEC101Apci::~IEC101Apci()
{

}

bool IEC101Apci::init(const QByteArray& buff)
{
	setDefault(buff);

	if(buff.count() < 2 + mConfig.addrLen)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度不足");
		return false;
	}
	flag = *(buff.data() + mLen);

	if(flag == 0x68)
	{

		mText.append(CharToHexStr(buff.data() + mLen) + "\t启动字符:0x68\r\n");
		mLen++;

		int lengthlen = stringToInt(mConfig.lengthType);
		if(lengthlen == 0)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未知的长度域类型");
			return false;
		}
		if(mConfig.lengthType == IEC_DOUBLESAME)
		{
			length = *(uchar *)(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t长度域1:" + QString::number(length) + "\r\n");
			mLen++;

			uchar length2 = *(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t长度域2:" + QString::number(length2) + "\r\n");
			mLen++;

			if(length != length2)
			{
				mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度域不同");
				return false;
			}
		}
		else if(mConfig.lengthType == IEC_SINGLE || mConfig.lengthType == IEC_DOUBLEDIFF)
		{
			length = charTouint(buff.data() + mLen, lengthlen);
			mText.append(CharToHexStr(buff.data() + mLen, lengthlen) + "\t长度域:" + QString::number(length) + "\r\n");
			mLen += lengthlen;
		}

		if(buff.count() < 3 + lengthlen + mConfig.addrLen)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度不足");
			return false;
		}

		uchar flag2 = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t启动字符:0x68\r\n");
		mLen++;
		if(flag2 != flag)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！第二个标志位错误");
			return false;
		}

	}
	else if(flag == 0x10)
	{
		mText.append(CharToHexStr(buff.data() + mLen) + "\t启动字符:0x10\r\n");
		mLen++;
		length = 1 + mConfig.addrLen;
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + mLen) + "\t出错！启动字符不是0x68");
		return false;
	}

	if(!code.init(buff.mid(mLen, 1)))
	{
		return false;
	}
	mMasterState = code.mMasterState;
	mSlaveState = code.mSlaveState;
	mText.append(code.showToText());
	mLen++;

	addr = charTouint(buff.data() + mLen, mConfig.addrLen);
	mText.append(CharToHexStr(buff.data() + mLen, mConfig.addrLen) + "\t地址域:" + QString::number(addr) + "\r\n");
	mLen += mConfig.addrLen;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;

}


