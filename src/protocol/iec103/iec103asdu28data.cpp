#include "iec103asdu28data.h"

IEC103Asdu28Data::IEC103Asdu28Data()
{
	datauchar1 = 0;
	datauchar2 = 0;
	fan = 0;
}

IEC103Asdu28Data::~IEC103Asdu28Data()
{

}

bool IEC103Asdu28Data::handle(const QByteArray& buff)
{
	datauchar1 = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t未定义,固定为0"  + "\r\n");
	len++;

	datauchar2 = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t未定义,固定为0"  + "\r\n");
	len++;

	fan = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	len += 2;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu28Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
