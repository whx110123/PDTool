#include "iec103asdu24data.h"

IEC103Asdu24Data::IEC103Asdu24Data()
{
	too = 0;
	tov = 0;
	fan = 0;
	acc = 0;
}

IEC103Asdu24Data::~IEC103Asdu24Data()
{

}

bool IEC103Asdu24Data::handle(const QByteArray& buff)
{
	too = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + tooToText(too) + "\r\n");
	len++;

	tov = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + tovToText(tov) + "\r\n");
	len++;

	fan = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	len += 2;

	acc = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + accToText(acc) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu24Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
