#include "iec103asdu30data.h"

IEC103Asdu30Data::IEC103Asdu30Data()
{
	datauchar = 0;
	tov = 0;
	fan = 0;
	acc = 0;
	ndv = 0;
	nfe = 0;
}

IEC103Asdu30Data::~IEC103Asdu30Data()
{
	sdvs.clear();
}

bool IEC103Asdu30Data::handle(const QByteArray& buff)
{
	sdvs.clear();

	datauchar = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t未定义,固定为0"  + "\r\n");
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

	ndv = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t扰动值数目NDV:" + QString::number(nfe) + "\r\n");
	len++;

	nfe = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t第一个信息元素的序号NFE:" + QString::number(nfe) + "\r\n");
	len += 2;

	for(int i = 0; i < ndv; i++)
	{
		short sdv = charToint(buff.data() + len, 2);
		mText.append(CharToHexStr(buff.data() + len, 2) + "\t单个扰动值SDV" + QString::number(i + 1) + ": " + QString::number(sdv));
		mText.append("\t对应序号为" + QString::number(nfe + i) + "\r\n");
		sdvs.append(sdv);
		len += 2;
	}

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu30Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
