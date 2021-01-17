#include "iec101asdu45data.h"

IEC101Asdu45Data::IEC101Asdu45Data()
{
	sco = 0;
}

IEC101Asdu45Data::~IEC101Asdu45Data()
{

}

bool IEC101Asdu45Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	sco = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + scsToText(sco) + "   " + seToText(sco) + "   " + quToText_iec101(sco) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}


bool IEC101Asdu45Data::createData(IECDataConfig& config)
{
	config.data += uintToBa(config.infaddr, mInfaddrlen);
	config.data += config.infdata;
	return true;
}
