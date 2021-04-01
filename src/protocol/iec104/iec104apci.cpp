#include "iec104apci.h"

IEC104Control::IEC104Control(const MyConfig& Config) : MyBase(Config)
{
	type = 0;
	code = 0;
	remoteSendNo = 0;
	remoteRecvNo = 0;
	localSendNo = 0;
	localRecvNo = 0;
}

IEC104Control::~IEC104Control()
{

}

bool IEC104Control::init(const QByteArray& buff)
{
	setDefault(buff);

	if(buff.count() < 4)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度小于4");
		return false;
	}

	code = *(buff.data() + mLen);
	if(code & 0x01)
	{
		if(code & 0x02)
		{
			type = UTYPE;
		}
		else
		{
			type = STYPE;
		}
	}
	else
	{
		type = ITYPE;
	}

	switch(type)
	{
	case UTYPE:
	{
		mText.append(CharToHexStr(buff.data() + mLen) + "\tU帧报文(bit1-2):3 无编号，起控制链路等功能\r\n\t");
		int sum = 0;
		if(code & 0x80)
		{
			mText.append("(bit8):80 确认TESTFR，响应测试\r\n");
			sum++;
		}
		if(code & 0x40)
		{
			mText.append("(bit7):40 激活TESTFR，启用测试\r\n");
			sum++;
		}
		if(code & 0x20)
		{
			mText.append("(bit6):20 子站确认STOPDT，子站响应停止链路\r\n");
			sum++;
		}
		if(code & 0x10)
		{
			mText.append("(bit5):10 主站激活STOPDT，主站停止链路\r\n");
			sum++;
		}
		if(code & 0x08)
		{
			mText.append("(bit4):8 子站确认STARTDT，子站响应激活链路\r\n");
			sum++;
		}
		if(code & 0x04)
		{
			mText.append("(bit3):4 主站激活STARTDT，主站激活链路\r\n");
			sum++;
		}

		if(sum == 0)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！此U帧报文未包含任何控制功能");
			return false;
		}
		else if(sum > 1)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！此U帧报文包含2种或2种以上控制功能");
			return false;
		}
		mLen++;

		for(int i = 0; i < 3; i++)
		{
			if(*(buff.data() + mLen) != 0)
			{
				mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！U帧控制域后3个字节出现不为0的数据");
				return false;
			}
			mText.append(CharToHexStr(buff.data() + mLen) + "\t固定为0x00\r\n");
			mLen++;
		}
		break;
	}
	case STYPE:

		if(code != 0x01)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + mLen) + "\t出错！当此字节后2位bit是0和1，可以确定是S帧，但S帧其他bit必须为0，条件不满足，因此报文有问题");
			return false;
		}
		mText.append(CharToHexStr(buff.data() + mLen) + "\tS帧报文(bit1-2):1 带编号，用于监视报文序号\r\n");
		mLen++;
		if(*(buff.data() + mLen) != 0)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + mLen) + "\t出错！已确定此帧报文是S帧，但S帧这个位置固定为0，条件不满足，因此报文有问题");
			return false;
		}
		mText.append(CharToHexStr(buff.data() + mLen) + "\t固定为0x00\r\n");
		mLen++;
		remoteRecvNo = charTouint(buff.data() + mLen, 2);
		if(remoteRecvNo % 2)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + mLen, 2) + "\t出错！接受序列号低字节，最后一个bit位必须为0，所以此数字必须为偶数，条件不满足，因此报文有问题");
			return false;
		}
		remoteRecvNo /= 2;
		localSendNo = remoteRecvNo;		//根据对面序号修改
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t接受序号: " + QString::number(remoteRecvNo) + "\r\n");
		mLen += 2;
		break;
	case ITYPE:

		remoteSendNo = charTouint(buff.data() + mLen, 2);
		remoteSendNo /= 2;
		localRecvNo = remoteSendNo + 1;	//根据对面序号修改
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t发送序号: " + QString::number(remoteSendNo) + "\r\n");
		mLen += 2;

		remoteRecvNo = charTouint(buff.data() + mLen, 2);
		if(remoteRecvNo % 2)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + mLen, 2) + "\t出错！接受序列号低字节，最后一个bit位必须为0，所以此数字必须为偶数，条件不满足，因此报文有问题");
			return false;
		}
		remoteRecvNo /= 2;
		localSendNo = remoteRecvNo;		//根据对面序号修改
		mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t接受序号: " + QString::number(remoteRecvNo) + "\r\n");
		mLen += 2;
		break;
	default:
		break;
	}
	if(mLen != 4)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！控制字节不足4个");
		return false;
	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}


bool IEC104Control::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);
	switch(type)
	{
	case ITYPE:
		tmp.data += uintToBa(localSendNo * 2, 2);
		tmp.data += uintToBa(localRecvNo * 2, 2);
		break;
	case UTYPE:
		tmp.data += code;
		tmp.data += uintToBa(0, 3);
		break;
	case STYPE:
		tmp.data += uintToBa(1, 2);;
		tmp.data += uintToBa(localRecvNo * 2, 2);
		break;
	default:
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
		return false;
		break;
	}
	if(proData.reverse)
	{
		proData = tmp + proData;
	}
	else
	{
		proData = proData + tmp;
	}
	return true;
}
IEC104Apci::IEC104Apci(const MyConfig& Config): MyBase(Config), control(Config)
{
	first = 0x68;
	length = 0;
}

IEC104Apci::~IEC104Apci()
{

}

bool IEC104Apci::init(const QByteArray& buff)
{
	setDefault(buff);


	first = *(buff.data() + mLen);
	if(first != 0x68)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + mLen) + "\t出错！启动字符不是0x68");
		return false;
	}

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
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未知的长度域类型");
		return false;
	}
	else if(mConfig.lengthType == IEC_SINGLE || mConfig.lengthType == IEC_DOUBLEDIFF)
	{
		length = charTouint(buff.data() + mLen, lengthlen);
		mText.append(CharToHexStr(buff.data() + mLen, lengthlen) + "\t长度域:" + QString::number(length) + "\r\n");
		mLen += lengthlen;
	}

	if(buff.length() < lengthlen + 5)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度不足，条件不满足，因此报文有问题");
		return false;
	}

	if(!control.init(buff.mid(mLen, 4)))
	{
		return false;
	}
	mLen += 4;
	mText.append(control.showToText());
	if(buff.length() == mLen)
	{
		return true;
	}
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	if(!handle(buff))
	{
		return false;
	}
	return true;

}

bool IEC104Apci::handle(const QByteArray& buff)
{
	mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未解析相关部分");
	return false;
}


QString IEC104Apci::showToText()
{
	QString text(mText);
	return text;
}

bool IEC104Apci::createData(MyData& proData)
{
	MyData tmp1;
	tmp1.getAttribute(proData);
	if(!control.createData(tmp1))
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
		return false;
	}

	MyData tmp2;
	tmp2.getAttribute(proData);
	tmp2.data += 0x68;
	if(proData.reverse)
	{
		tmp2.data += uintToBa(tmp1.data.length() + proData.data.length(), stringToInt(mConfig.lengthType));
		proData = tmp2 + tmp1 + proData;
	}
	else
	{
		tmp2.data += uintToBa(tmp1.data.length(), stringToInt(mConfig.lengthType));
		proData = proData + tmp2 + tmp1;
	}
	return true;
}


