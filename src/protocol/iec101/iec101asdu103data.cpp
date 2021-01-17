#include "iec101asdu103data.h"

IEC101Asdu103Data::IEC101Asdu103Data()
{

}

IEC101Asdu103Data::~IEC101Asdu103Data()
{

}

bool IEC101Asdu103Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	datetime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}


bool IEC101Asdu103Data::createData(IECDataConfig& config)
{
	if(config.isfirst || (config.vsq & 0x80) == 0)
	{
		infaddr = 0;
		config.data += uintToBa(infaddr, mInfaddrlen);
	}
	datetime = QDateTime::currentDateTime();
	if(config.isMaster)
	{
		config.data += dateTimeToBa(datetime, 7, BINARYTIME2A);
	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
		return false;
	}
	config.isfirst = false;
	return true;
}
