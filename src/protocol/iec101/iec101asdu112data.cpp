#include "iec101asdu112data.h"

IEC101Asdu112Data::IEC101Asdu112Data()
{
	floatdata = 0;
	qpm = 0;
}

IEC101Asdu112Data::~IEC101Asdu112Data()
{

}

bool IEC101Asdu112Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	floatdata = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");
	len += 4;

	qpm = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + qpmToText(qpm) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu112Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
