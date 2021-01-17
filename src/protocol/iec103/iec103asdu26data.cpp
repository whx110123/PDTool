#include "iec103asdu26data.h"

IEC103Asdu26Data::IEC103Asdu26Data()
{
	datauchar = 0;
	tov = 0;
	fan = 0;
	nof = 0;
	noc = 0;
	noe = 0;
	_int = 0;
}

IEC103Asdu26Data::~IEC103Asdu26Data()
{

}

bool IEC103Asdu26Data::handle(const QByteArray& buff)
{
	datauchar = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t未定义,固定为0"  + "\r\n");
	len++;

	tov = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + tovToText(tov) + "\r\n");
	len++;

	fan = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	len += 2;

	nof = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t电网故障序号NOF:" + QString::number(nof) + "\r\n");
	len += 2;

	noc = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t通道数目NOC:" + QString::number(noc) + "\r\n");
	len++;

	noe = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t一个通道信息元素的数目NOE:" + QString::number(noe) + "\r\n");
	len += 2;

	_int = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t信息元素间的间隔INT:" + QString::number(_int) + "   单位:微秒\r\n");
	len += 2;

	datetime = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 4));
	len += 4;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;

}

bool IEC103Asdu26Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
