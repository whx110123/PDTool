#include "iec103asdu102data.h"

IEC103Asdu102Data::IEC103Asdu102Data()
{
	gbk = QTextCodec::codecForName("GB18030");
}

IEC103Asdu102Data::~IEC103Asdu102Data()
{
	files.clear();
}

bool IEC103Asdu102Data::handle(const QByteArray& buff)
{
	files.clear();

	rii = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	len++;

	isLast = *(buff.data() + len) & 0x01;
	mText.append(CharToHexStr(buff.data() + len) + "\t后续位标志: " + QString(isLast ? "1 有后续帧" : "0 最后的帧") + "\r\n");
	len++;

	fileNum = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t本帧包含文件数:" + QString::number(fileNum) + "\r\n");
	len += 2;

	dtBegin = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	dtEnd = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	for(int i = 0; i < fileNum; i++)
	{
		NormalFileInfo info;

		QByteArray ba(buff.data() + len, 100);
		info.fileName = gbk->toUnicode(ba);
		mText.append(CharToHexStr(buff.data() + len, 100) + "\t文件" + QString::number(i + 1) + "文件名: " + info.fileName + "\r\n");
		len += 100;
		info.dt = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, 7));
		len += 7;
		info.fileSize = charTouint(buff.data() + len, 4);
		mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件" + QString::number(i + 1) + "文件大小: " + QString::number(info.fileSize) + "\r\n");
		len += 4;

		files.append(info);

	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}
