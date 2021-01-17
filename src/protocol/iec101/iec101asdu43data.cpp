#include "iec101asdu43data.h"

IEC101Asdu43Data::IEC101Asdu43Data()
{

}

IEC101Asdu43Data::~IEC101Asdu43Data()
{

}

bool IEC101Asdu43Data::init(const QByteArray& buff)
{
	setDefault(buff);

	cont = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + contToText() + "\r\n");
	len++;

	fileindex = charTouint(buff.data() + len, 4);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t起始传输位置:" + QString::number(fileindex) + "\r\n");
	len += 4;

	QByteArray ba(buff.data() + len, buff.length() - len - 1);
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	filedata = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + len, buff.length() - len - 1) + "\t文件内容:\r\n" + filedata + "\r\n");
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	len = buff.length() - 1;

	uchar crctmp = crcsum(buff.data(), 5, len - 1);
	crc = *(buff.data() + len);
	if(crc != crctmp)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！校验错误");
		return false;
	}
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC101Asdu43Data::showToText()
{
	QString text = mText;
	text.append(CharToHexStr(crc) + "\t校验和\r\n");
	return text;
}

bool IEC101Asdu43Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

QString IEC101Asdu43Data::contToText()
{
	QString text = "后续位标志(bit1): " + QString::number(cont) + "  ";
	switch(cont)
	{
	case 0:
		text.append("无后续帧");
		break;
	case 1:
		text.append("有后续帧");
		break;
	default:
		text.append("未识别标志");
		break;
	}
	return text;
}
