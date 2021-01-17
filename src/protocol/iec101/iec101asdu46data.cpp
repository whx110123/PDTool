#include "iec101asdu46data.h"

IEC101Asdu46Data::IEC101Asdu46Data()
{
	dco = 0;
}

IEC101Asdu46Data::~IEC101Asdu46Data()
{

}

bool IEC101Asdu46Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	dco = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dcsToText(dco) + "   " + seToText(dco) + "   " + quToText_iec101(dco) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu46Data::createData(IECDataConfig& config)
{
	config.data += uintToBa(config.infaddr, mInfaddrlen);
	config.data += config.infdata;
	return true;
}
