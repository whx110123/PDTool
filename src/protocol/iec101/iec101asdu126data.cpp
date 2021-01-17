#include "iec101asdu126data.h"

IEC101Asdu126Data::IEC101Asdu126Data()
{
	nof = 0;
	lof = 0;
	sof = 0;
}

IEC101Asdu126Data::~IEC101Asdu126Data()
{

}

bool IEC101Asdu126Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");

	nof = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t文件名或者子目录名NOF: " + QString::number(nof) + "\r\n");
	len += 2;

	lof = charTouint(buff.data() + len, 3);
	mText.append(CharToHexStr(buff.data() + len, 3) + "\t文件长度LOF: " + QString::number(lof) + "\r\n");
	len += 3;

	sof = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + sofToText_iec101(sof) + "\r\n");
	len++;

	datetime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu126Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
