#include "iec101asdu70data.h"

IEC101Asdu70Data::IEC101Asdu70Data()
{
	coi = 0;
	infaddr = 0;
}

IEC101Asdu70Data::~IEC101Asdu70Data()
{

}

bool IEC101Asdu70Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	coi = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + coiToText(coi) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}


bool IEC101Asdu70Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

