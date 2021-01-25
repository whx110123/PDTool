#include "iec103asdu103data.h"

IEC103Asdu103Data::IEC103Asdu103Data()
{
	gbk = QTextCodec::codecForName("GB18030");
}

IEC103Asdu103Data::~IEC103Asdu103Data()
{

}

bool IEC103Asdu103Data::handle(const QByteArray& buff)
{
	rii = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	len++;

	QByteArray ba(buff.data() + len, 100);
	fileName = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + len, 100) + "\t文件名100个字节:   " + fileName + "\r\n");
	len += 100;

	fileIndex = charTouint(buff.data() + len, 4);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t起始传输位置: " + QString::number(fileIndex) + "\r\n");
	len += 4;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}
