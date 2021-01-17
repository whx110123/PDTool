#include "iec101asdu137data.h"

IEC101Asdu137Data::IEC101Asdu137Data()
{
	shortdata = 0;
	qos = 0;
}

IEC101Asdu137Data::~IEC101Asdu137Data()
{

}

bool IEC101Asdu137Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	shortdata = charToint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");
	len += 2;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len + 8 == buff.length())
	{
		qos = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\t" + qosToText(qos) + "\r\n");
		len++;

		datetime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, 7));
		len += 7;
		mText.append("-----------------------------------------------------------------------------------------------\r\n");
	}
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}


bool IEC101Asdu137Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
