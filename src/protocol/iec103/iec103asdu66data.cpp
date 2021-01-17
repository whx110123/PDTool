#include "iec103asdu66data.h"

IEC103Asdu66Data::IEC103Asdu66Data()
{
	shortdata = 0;
	qos = 0;
}

IEC103Asdu66Data::~IEC103Asdu66Data()
{

}

bool IEC103Asdu66Data::handle(const QByteArray& buff)
{
	shortdata = charToint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t设定值:" + QString::number(shortdata) + "\r\n");
	len += 2;

	qos = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + qosToText(qos) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu66Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
