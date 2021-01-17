#include "iec104apci.h"

IEC104Control::IEC104Control()
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
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度小于4");
		return false;
	}
	masterState = STATE_NORMAL;
	slaveState = STATE_NORMAL;

	code = *(buff.data() + len);
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
			mText.append(CharToHexStr(buff.data() + len) + "\tU帧报文(bit1-2):3 无编号，起控制链路等功能\r\n\t");
			int sum = 0;
			if(code & 0x80)
			{
				mText.append("(bit8):80 确认TESTFR，响应测试\r\n");
				masterState = STATE_TESTACT;
				slaveState = STATE_TESTACT;
				sum++;
			}
			if(code & 0x40)
			{
				mText.append("(bit7):40 激活TESTFR，启用测试\r\n");
				masterState = STATE_TESTCONFIRM;
				slaveState = STATE_TESTCONFIRM;
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
				masterState = STATE_CALLALL;
				sum++;
			}
			if(code & 0x04)
			{
				mText.append("(bit3):4 主站激活STARTDT，主站激活链路\r\n");
				slaveState = STATE_INIT;
				sum++;
			}

			if(sum == 0)
			{
				error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！此U帧报文未包含任何控制功能");
				return false;
			}
			else if(sum > 1)
			{
				error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！此U帧报文包含2种或2种以上控制功能");
				return false;
			}
			len++;

			for(int i = 0; i < 3; i++)
			{
				if(*(buff.data() + len) != 0)
				{
					error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！U帧控制域后3个字节出现不为0的数据");
					return false;
				}
				mText.append(CharToHexStr(buff.data() + len) + "\t固定为0x00\r\n");
				len++;
			}
			break;
		}
	case STYPE:

		if(code != 0x01)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + len) + "\t出错！当此字节后2位bit是0和1，可以确定是S帧，但S帧其他bit必须为0，条件不满足，因此报文有问题");
			return false;
		}
		mText.append(CharToHexStr(buff.data() + len) + "\tS帧报文(bit1-2):1 带编号，用于监视报文序号\r\n");
		len++;
		if(*(buff.data() + len) != 0)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + len) + "\t出错！已确定此帧报文是S帧，但S帧这个位置固定为0，条件不满足，因此报文有问题");
			return false;
		}
		mText.append(CharToHexStr(buff.data() + len) + "\t固定为0x00\r\n");
		len++;
		remoteRecvNo = charTouint(buff.data() + len, 2);
		if(remoteRecvNo % 2)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + len, 2) + "\t出错！接受序列号低字节，最后一个bit位必须为0，所以此数字必须为偶数，条件不满足，因此报文有问题");
			return false;
		}
		remoteRecvNo /= 2;
		localSendNo = remoteRecvNo;		//根据对面序号修改
		mText.append(CharToHexStr(buff.data() + len, 2) + "\t接受序号: " + QString::number(remoteRecvNo) + "\r\n");
		len += 2;
		masterState = STATE_TESTACT;
		slaveState = STATE_NORMAL;
		break;
	case ITYPE:

		remoteSendNo = charTouint(buff.data() + len, 2);
		remoteSendNo /= 2;
		localRecvNo = remoteSendNo + 1;	//根据对面序号修改
		mText.append(CharToHexStr(buff.data() + len, 2) + "\t发送序号: " + QString::number(remoteSendNo) + "\r\n");
		len += 2;

		remoteRecvNo = charTouint(buff.data() + len, 2);
		if(remoteRecvNo % 2)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + len, 2) + "\t出错！接受序列号低字节，最后一个bit位必须为0，所以此数字必须为偶数，条件不满足，因此报文有问题");
			return false;
		}
		remoteRecvNo /= 2;
		localSendNo = remoteRecvNo;		//根据对面序号修改
		mText.append(CharToHexStr(buff.data() + len, 2) + "\t接受序号: " + QString::number(remoteRecvNo) + "\r\n");
		len += 2;
		masterState = STATE_NORMAL;
		slaveState = STATE_NORMAL;
		break;
	default:
		break;
	}
	if(len != 4)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！控制字节不足4个");
		return false;
	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}


bool IEC104Control::createData(IECDataConfig& config)
{
	if(config.isMaster)
	{
		switch(config.controltype)
		{
		case UTYPE:
			switch(config.masterState)
			{
			case STATE_INIT:
				config.data += 0x07;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			case STATE_NORMAL:
				break;
			case STATE_TESTACT:
				config.data += 0x43;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			case STATE_TESTCONFIRM:
				config.data += 0x83;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			default:
				error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的主站状态");
				return false;
				break;
			}
			config.asdutype = 0;
			break;
		case STYPE:

			config.data += 0x01;
			config.data += '\0';
			config.data += uintToBa(localRecvNo << 1, 2);
			config.asdutype = 0;
			break;
		case ITYPE:
			config.data += uintToBa(localSendNo << 1, 2);
			config.data += uintToBa(localRecvNo << 1, 2);
			localSendNo++;

			break;
		default:
			break;
		}
	}
	else
	{
		switch(config.controltype)
		{
		case UTYPE:
			switch(config.slaveState)
			{
			case STATE_INIT:
				config.data += 0x0b;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			case STATE_NORMAL:
				break;
			case STATE_TESTACT:
				config.data += 0x43;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			case STATE_TESTCONFIRM:
				config.data += 0x83;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			default:
				error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的子站状态");
				return false;
				break;
			}
			config.asdutype = 0;
			break;
		case STYPE:
			config.data += 0x01;
			config.data += '\0';
			config.data += uintToBa(localRecvNo << 1, 2);
			config.asdutype = 0;
			break;
		case ITYPE:
			config.data += uintToBa(localSendNo << 1, 2);
			config.data += uintToBa(localRecvNo << 1, 2);
			localSendNo++;
			break;
		default:
			break;
		}
	}

	return true;
}
IEC104Apci::IEC104Apci()
{
	first = 0;
	length = 0;

	mLengthType = mConfig.lengthType;
}

IEC104Apci::~IEC104Apci()
{

}

bool IEC104Apci::init(const QByteArray& buff)
{
	setDefault(buff);


	first = *(buff.data() + len);
	if(first != 0x68)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + len) + "\t出错！启动字符不是0x68");
		return false;
	}

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
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未知的长度域类型");
		return false;
	}
	else if(mLengthType == IEC_SINGLE || mLengthType == IEC_DOUBLEDIFF)
	{
		length = charTouint(buff.data() + len, lengthlen);
		mText.append(CharToHexStr(buff.data() + len, lengthlen) + "\t长度域:" + QString::number(length) + "\r\n");
		len += lengthlen;
	}

	if(buff.length() < lengthlen + 5)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度不足，条件不满足，因此报文有问题");
		return false;
	}

	if(!control.init(buff.mid(len, 4)))
	{
		return false;
	}
	len += 4;
	masterState = control.masterState;
	slaveState = control.slaveState;
	mText.append(control.showToText());
	if(buff.length() == len)
	{
		return true;
	}
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
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
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未解析相关部分");
	return false;
}


QString IEC104Apci::showToText()
{
	QString text(mText);
	return text;
}

bool IEC104Apci::createData(IECDataConfig& config)
{
	config.data += 0x68;
	config.data += '\0';
	if(!control.createData(config))
	{
		return false;
	}
	return true;
}


