#include "iec103asdu5data.h"

IEC103Asdu5Data::IEC103Asdu5Data()
{
	col = 0;
	memset(ch, 0, sizeof(ch));
}

IEC103Asdu5Data::~IEC103Asdu5Data()
{

}

bool IEC103Asdu5Data::handle(const QByteArray& buff)
{

	col = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + colToText(col) + "\r\n");
	len++;

	QByteArray ba(buff.data() + len, 8);
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	gbkstr = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + len, 8) + "\tASCII: " + gbkstr + "\r\n");
	len += 8;

	memcpy(ch, buff.data() + len, 4);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t用户自定义字符\r\n");
	len += 4;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu5Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
