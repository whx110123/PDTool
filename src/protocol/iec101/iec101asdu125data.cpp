#include "iec101asdu125data.h"

IEC101Asdu125Data::IEC101Asdu125Data()
{
	nof = 0;
	nos = 0;
	los = 0;
}

IEC101Asdu125Data::~IEC101Asdu125Data()
{

}

bool IEC101Asdu125Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");

	nof = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t文件名称NOF: " + QString::number(nof) + "\r\n");
	len += 2;

	nos = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t节名称NOS: " + QString::number(nos) + "\r\n");
	len++;

	los = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t段的长度: " + QString::number(los) + "\r\n");
	len++;

	QByteArray ba(buff.data() + len, los);
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	gbkstr = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + len, los) + "\t段内容:\r\n" + gbkstr + "\r\n");
	len += los;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu125Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
