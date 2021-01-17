#include "modbustcp.h"

ModbusTCP::ModbusTCP()
{
	flagIndex = 0;
	flag = 0;
	length = 0;
}

ModbusTCP::~ModbusTCP()
{

}

bool ModbusTCP::init(const QByteArray& buff)
{
	setDefault(buff);

	if(buff.length() < 10)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！modbus TCP报文过短");
		return false;
	}
	flagIndex = charTouint(buff.data() + len, 2, 1);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t事务处理标识: " + QString::number(flagIndex) + "\r\n");
	len += 2;

	flag = charTouint(buff.data() + len, 2, 1);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t协议标识符: " + QString::number(flag) + "\r\n");
	len += 2;

	if(flag != 0)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！modbus TCP协议标识符必须为0");
		return false;
	}
	length = charTouint(buff.data() + len, 2, 1);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t长度: " + QString::number(length) + "\r\n");
	len += 2;
	if(length > 255)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！modbus TCP长度大于255");
		return false;
	}
	if(length + 6 > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！modbus TCP长度比实际报文长度长");
		return false;
	}

	if(length == *(uchar *)(buff.data() + len + 2) + 3)
	{
		mb.isMaster = false;
	}
	else
	{
		mb.isMaster = true;
	}


	if(!mb.init(buff.mid(len, length)))
	{
		return false;
	}

	if(length != mb.len)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！modbus TCP报文解析错误");
		return false;
	}

	len += length;
	mRecvData = buff.left(len);
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString ModbusTCP::showToText()
{
	mText.append(mb.showToText());
	return mText;
}
