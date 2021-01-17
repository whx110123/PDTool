#include "iec101asdu104data.h"

IEC101Asdu104Data::IEC101Asdu104Data()
{
	ushortData = 0;
}

IEC101Asdu104Data::~IEC101Asdu104Data()
{

}

bool IEC101Asdu104Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	ushortData = charTouint(buff.data() + len, 2);
	if(ushortData != 0x55AA)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！固定测试字不是0x55AA"));
		return false;
	}
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t固定测试字FBP: 0x55AA\r\n");
	len += 2;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu104Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
