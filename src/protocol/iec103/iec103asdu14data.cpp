#include "iec103asdu14data.h"

IEC103Asdu14Data::IEC103Asdu14Data()
{

}

IEC103Asdu14Data::~IEC103Asdu14Data()
{

}

bool IEC103Asdu14Data::handle(const QByteArray& buff)
{
	rii = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	len++;

	isLast = *(buff.data() + len) & 0x01;
	mText.append(CharToHexStr(buff.data() + len) + "\t后续位标志: " + QString(isLast ? "1 有后续帧" : "0 最后的帧") + "\r\n");
	len++;

	if(len == buff.size())
	{
		return true;
	}
	fileIndex = charTouint(buff.data() + len, 4);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t起始传输位置: " + QString::number(fileIndex) + "\r\n");
	len += 4;

	fileData = buff.mid(len);
	mText.append(CharToHexStr(buff.data() + len, fileData.length()) + "\t文件数据: \r\n");
	len += fileData.length();

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}
