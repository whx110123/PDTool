#include "measuredterminalapci.h"

MTApci::MTApci(const MyConfig& Config): MyBase(Config), code(Config)
{
	flag = 0;
	length = 0;
	A1 = 0;
	A2 = 0;
	A3 = 0;
}

MTApci::~MTApci()
{

}

bool MTApci::init(const QByteArray& buff)
{
	setDefault(buff);

	if(buff.count() < 12)
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
		else if(mConfig.lengthType == IEC_FOURDIFF)
		{
			length = charTouint(buff.data() + mLen, 2);
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t长度域:" + QString::number(length) + "\r\n");
			mLen += 2;

			ushort length2 = charTouint(buff.data() + mLen, 2);
			mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t长度域2:" + QString::number(length2) + "\r\n");
			mLen += 2;

			if(length != length2)
			{
				mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度域不同");
				return false;
			}
		}

		if(buff.count() < 10 + lengthlen)
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

	A1 = charTouint(buff.data() + mLen, 3);
	mText.append(CharToHexStr(buff.data() + mLen, 3) + "\t" + A1ToText() + "\r\n");
	mLen += 3;

	A2 = charTouint(buff.data() + mLen, 3);
	mText.append(CharToHexStr(buff.data() + mLen, 3) + "\t终端地址:" + QString::number(A2) + "\r\n");
	mLen += 3;

	A3 = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t主站地址:" + QString::number(A3) + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


QString MTApci::A1ToText()
{
	QString text;
	text.append("省地市区县码A1:  ");
	text.append(QString("区县码=%1,地市码=%2,省份码=%3").arg(QString::number(A1 & 0xff, 16)).arg(QString::number((A1 >> 8) & 0xff, 16)).arg(QString::number((A1 >> 16) & 0xff, 16)));
	return text;
}
