#include "iec101asdu100data.h"

IEC101Asdu100Data::IEC101Asdu100Data()
{
	qoi = 0;
	infaddr = 0;
}

IEC101Asdu100Data::~IEC101Asdu100Data()
{

}

bool IEC101Asdu100Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	qoi = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + qoiToText(qoi) + "\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu100Data::createData(IECDataConfig& config)
{

	if(config.isfirst || (config.vsq & 0x80) == 0)
	{
		infaddr = 0;
		config.data += uintToBa(infaddr, mInfaddrlen);
	}

	if(config.isMaster)
	{
		config.data += 0x14;
	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
		return false;
	}
	config.isfirst = false;
	return true;
}
