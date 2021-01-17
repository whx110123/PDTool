#include "iec101asdu124data.h"

IEC101Asdu124Data::IEC101Asdu124Data()
{
	nof = 0;
	nos = 0;
	afq = 0;
}

IEC101Asdu124Data::~IEC101Asdu124Data()
{

}

bool IEC101Asdu124Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");

	nof = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t文件名称NOF: " + QString::number(nof) + "\r\n");
	len += 2;

	nos = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t节名称NOS: " + QString::number(nos) + "\r\n");
	len++;

	afq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + afqToText_iec101(afq) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu124Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
