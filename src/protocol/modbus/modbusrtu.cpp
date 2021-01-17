#include "modbusrtu.h"

ModbusRTU::ModbusRTU()
{
	crc = 0;
}

ModbusRTU::~ModbusRTU()
{

}

bool ModbusRTU::init(const QByteArray& buff)
{
	setDefault(buff);

	bool isOk = false;
	int i = 3;
	while(i + 1 < buff.length() && i < 255)
	{
		crc = charTouint(buff.data() + i, 2);
		if(crc16((uchar *)buff.data(), i) == crc)
		{

			isOk = true;
			break;
		}
		i++;
	}
	len += i;
	if(!isOk)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未发现正确的modbus RTU报文");
		return false;
	}

	if((int) * (buff.data() + 2) == len - 3)
	{
		mb.isMaster = false;
	}
	else
	{
		mb.isMaster = true;
	}

	if(!mb.init(buff.left(len)))
	{
		return false;
	}

	if(len != mb.len)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！modbus RTU报文解析错误");
		return false;
	}

	len += 2;
	mRecvData = buff.left(len);
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;

}

QString ModbusRTU::showToText()
{
	mText.append(mb.showToText());
	mText.append(CharToHexStr(uintToBa(crc, 2).data(), 2) + "\t校验和\r\n");
	return mText;
}
