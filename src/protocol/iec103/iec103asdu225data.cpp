#include "iec103asdu225data.h"

IEC103Asdu225Data::IEC103Asdu225Data()
{
	fnam = 0;
	snam = 0;
	tmp = 0;
	dlen = 0;
}

IEC103Asdu225Data::~IEC103Asdu225Data()
{

}

bool IEC103Asdu225Data::handle(const QByteArray& buff)
{
	fnam = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t文件名称FNAM: " + QString::number(fnam) + "\r\n");
	len += 2;

	snam = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t节名称SNAM: " + QString::number(snam) + "\r\n");
	len++;

	tmp = charTouint(buff.data() + len, 2);
	if(len + 2 + tmp != buff.length())
	{
		mText.append(CharToHexStr(buff.data() + len, 2) + "\t未知: " + QString::number(tmp) + "\r\n");
		len += 2;
	}

	dlen = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t段长度: " + QString::number(dlen) + "\r\n");
	len += 2;

	if(len + dlen != buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！段长度错误");
		return false;
	}
	QByteArray ba(buff.data() + len, dlen);
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	gbkstr = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + len, dlen) + "\t段内容:\r\n" + gbkstr + "\r\n");
	len += dlen;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu225Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
