#include "iec103asdu102data.h"

IEC103Asdu102Data::IEC103Asdu102Data(const MyConfig& Config): IEC103Asdu101Data(Config)
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

	rii = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	mLen++;

	isLast = *(buff.data() + mLen) & 0x01;
	mText.append(CharToHexStr(buff.data() + mLen) + "\t后续位标志: " + QString(isLast ? "1 有后续帧" : "0 最后的帧") + "\r\n");
	mLen++;

	fileNum = charTouint(buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t本帧包含文件数:" + QString::number(fileNum) + "\r\n");
	mLen += 2;

	dtBegin = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	dtEnd = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + mLen, 7));
	mLen += 7;

	for(int i = 0; i < fileNum; i++)
	{
		NormalFileInfo info;

		QByteArray ba(buff.data() + mLen, 100);
		info.fileName = gbk->toUnicode(ba);
		mText.append(CharToHexStr(buff.data() + mLen, 100) + "\t文件" + QString::number(i + 1) + "文件名: " + info.fileName + "\r\n");
		mLen += 100;
		info.dt = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		info.fileSize = charTouint(buff.data() + mLen, 4);
		mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件" + QString::number(i + 1) + "文件大小: " + QString::number(info.fileSize) + "\r\n");
		mLen += 4;

		files.append(info);

	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}
