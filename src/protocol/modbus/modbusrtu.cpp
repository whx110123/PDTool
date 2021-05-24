#include "modbusrtu.h"

ModbusRTU::ModbusRTU(const MyConfig& Config): MyBase(Config), mb(Config)
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
	int ALL_LEN = i;
	if(!isOk)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未发现正确的modbus RTU报文");
		return false;
	}

	if((int) * (buff.data() + 2) == ALL_LEN - 3)
	{
		mb.isMaster = false;
	}
	else
	{
		mb.isMaster = true;
	}

	if(mb.isMaster && ALL_LEN < 6)
	{
		crc = charTouint(buff.data() + 6, 2);
		if(crc16((uchar *)buff.data(), 6) == crc)
		{
			ALL_LEN = 6;
		}
		else
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！modbus RTU下发报文校验错误");
			return false;
		}
	}

	if(!mb.init(buff.left(ALL_LEN)))
	{
		mText.append(mb.showToText());
		return false;
	}
	mText.append(mb.showToText());
	mLen += mb.mLen;
	if(ALL_LEN != mb.mLen)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！modbus RTU报文解析错误");
		return false;
	}

	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t校验和\r\n");
	mLen += 2;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;

}

