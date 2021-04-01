#include "modbustcp.h"

ModbusTCP::ModbusTCP(const MyConfig& Config): MyBase(Config), mb(Config)
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
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！modbus TCP报文过短");
		return false;
	}
	flagIndex = charTouint(buff.data() + mLen, 2, 1);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t事务处理标识: " + QString::number(flagIndex) + "\r\n");
	mLen += 2;

	flag = charTouint(buff.data() + mLen, 2, 1);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t协议标识符: " + QString::number(flag) + "\r\n");
	mLen += 2;

	if(flag != 0)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！modbus TCP协议标识符必须为0");
		return false;
	}
	length = charTouint(buff.data() + mLen, 2, 1);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t长度: " + QString::number(length) + "\r\n");
	mLen += 2;
	if(length > 255)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！modbus TCP长度(%1)大于255").arg(length));
		return false;
	}
	if(length + 6 > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！modbus TCP长度(%1)比实际报文长度(%2)长").arg(length + 6).arg(buff.length()));
		return false;
	}

	if(length == *(uchar *)(buff.data() + mLen + 2) + 3)
	{
		mb.isMaster = false;
	}
	else
	{
		mb.isMaster = true;
	}


	if(!mb.init(buff.mid(mLen, length)))
	{
		return false;
	}

	if(length != mb.mLen)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！modbus TCP报文解析错误");
		return false;
	}

	mLen += length;
	mRecvData = buff.left(mLen);
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

QString ModbusTCP::showToText()
{
	mText.append(mb.showToText());
	return mText;
}
