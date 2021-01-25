#include "iec103asdu13data.h"

IEC103Asdu13Data::IEC103Asdu13Data()
{
	gbk = QTextCodec::codecForName("GB18030");
}

IEC103Asdu13Data::~IEC103Asdu13Data()
{

}

bool IEC103Asdu13Data::handle(const QByteArray& buff)
{
	rii = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	len++;

	uchar waveFileNameLen;
	if(protocolName == IEC_103BAOXINNET_NW)
	{
		waveFileNameLen = 128;
	}
	else
	{
		waveFileNameLen = 64;
	}

	QByteArray ba(buff.data() + len, waveFileNameLen);
	waveFileName = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + len, waveFileNameLen) + "\t不含扩展名的录波文件名:   " + waveFileName + "\r\n");
	len += waveFileNameLen;

	fileIndex = charTouint(buff.data() + len, 4);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t起始传输位置: " + QString::number(fileIndex) + "\r\n");
	len += 4;

	if(protocolName != IEC_103BAOXINNET_NW)
	{
		no = charTouint(buff.data() + len, 4);
		mText.append(CharToHexStr(buff.data() + len, 4) + "\t录波文件在装置中的编号: " + QString::number(no) + "\r\n");
		len += 4;
	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}
