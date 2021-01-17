#include "iec103asdu223data.h"

IEC103Asdu223Data::IEC103Asdu223Data()
{
	fnam = 0;
	flen = 0;
	frq = 0;
}

IEC103Asdu223Data::~IEC103Asdu223Data()
{

}

bool IEC103Asdu223Data::handle(const QByteArray& buff)
{
	fnam = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t文件名称FNAM: " + QString::number(fnam) + "\r\n");
	len += 2;

	flen = charTouint(buff.data() + len, 4);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件长度FLEN: " + QString::number(flen) + "\r\n");
	len += 4;

	frq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + frqToText(frq) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu223Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
