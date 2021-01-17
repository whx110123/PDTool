#include "iec101asdu123data.h"

IEC101Asdu123Data::IEC101Asdu123Data()
{
	nof = 0;
	nos = 0;
	lsq = 0;
	chs = 0;
}

IEC101Asdu123Data::~IEC101Asdu123Data()
{

}

bool IEC101Asdu123Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");

	nof = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t文件名称NOF: " + QString::number(nof) + "\r\n");
	len += 2;

	nos = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t节名称NOS: " + QString::number(nos) + "\r\n");
	len++;

	lsq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + lsqToText_iec101(lsq) + "\r\n");
	len++;

	chs = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t校验和CHS\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu123Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
