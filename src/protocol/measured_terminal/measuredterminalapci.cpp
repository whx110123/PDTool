#include "measuredterminalapci.h"

MTApci::MTApci()
{
	flag = 0;
	length = 0;
	A1 = 0;
	A2 = 0;
	A3 = 0;
	mLengthType = mConfig.lengthType;
}

MTApci::~MTApci()
{

}

bool MTApci::init(const QByteArray& buff)
{
	setDefault(buff);

	if(buff.count() < 12)
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

		if(buff.count() < 10 + lengthlen)
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

	A1 = charTouint(buff.data() + len, 3);
	mText.append(CharToHexStr(buff.data() + len, 3) + "\t" + A1ToText() + "\r\n");
	len += 3;

	A2 = charTouint(buff.data() + len, 3);
	mText.append(CharToHexStr(buff.data() + len, 3) + "\t终端地址:" + QString::number(A2) + "\r\n");
	len += 3;

	A3 = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t主站地址:" + QString::number(A3) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool MTApci::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

QString MTApci::A1ToText()
{
	QString text;
	text.append("省地市区县码A1:  ");
	text.append(QString("区县码=%1,地市码=%2,省份码=%3").arg(QString::number(A1 & 0xff, 16)).arg(QString::number((A1 >> 8) & 0xff, 16)).arg(QString::number((A1 >> 16) & 0xff, 16)));
	return text;
}
