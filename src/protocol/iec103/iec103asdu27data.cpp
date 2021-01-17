#include "iec103asdu27data.h"

IEC103Asdu27Data::IEC103Asdu27Data()
{
	datauchar = 0;
	tov = 0;
	fan = 0;
	acc = 0;
	rpv = 0;
	rsv = 0;
	rfa = 0;
}

IEC103Asdu27Data::~IEC103Asdu27Data()
{

}

bool IEC103Asdu27Data::handle(const QByteArray& buff)
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

	acc = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + accToText(acc) + "\r\n");
	len++;

	rpv = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t一次额定值RPV:" + QString::number(rpv) + "\r\n");
	len += 4;

	rsv = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t二次额定值RSV:" + QString::number(rsv) + "\r\n");
	len += 4;

	rfa = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t参比因子RFA:" + QString::number(rfa) + "\r\n");
	len += 4;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu27Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
