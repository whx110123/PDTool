#include "iec103asdu16data.h"

IEC103Asdu16Data::IEC103Asdu16Data(const MyConfig& Config): IEC103Asdu15Data(Config)
{
	gbk = QTextCodec::codecForName("GB18030");
}

IEC103Asdu16Data::~IEC103Asdu16Data()
{
	files.clear();
}

bool IEC103Asdu16Data::handle(const QByteArray& buff)
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

	if(mConfig.protocolName == IEC_103BAOXINNET_NW)
	{
		for(int i = 0; i < fileNum; i++)
		{
			WaveFileInfo info;
			info.addr = *(buff.data() + mLen);
			mText.append(CharToHexStr(buff.data() + mLen) + "\t文件" + QString::number(i + 1) + "录波装置地址: " + QString::number(info.addr) + "\r\n");
			mLen++;
			QByteArray ba(buff.data() + mLen, 128);
			info.fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + mLen, 128) + "\t文件" + QString::number(i + 1) + "文件名: " + info.fileName + "\r\n");
			mLen += 128;
			info.dt = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
			mText.append(timeToText(buff.data() + mLen, 7));
			mLen += 7;
			info.fileSize = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件" + QString::number(i + 1) + "文件大小: " + QString::number(info.fileSize) + "\r\n");
			mLen += 4;

			files.append(info);

		}
	}
	else
	{
		for(int i = 0; i < fileNum; i++)
		{
			WaveFileInfo info;
			QByteArray ba(buff.data() + mLen, 64);
			info.fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + mLen, 64) + "\t文件" + QString::number(i + 1) + "文件名: " + info.fileName + "\r\n");
			mLen += 64;
			info.dt = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
			mText.append(timeToText(buff.data() + mLen, 7));
			mLen += 7;
			info.fileSize = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件" + QString::number(i + 1) + "文件大小: " + QString::number(info.fileSize) + "\r\n");
			mLen += 4;
			info.no = charTouint(buff.data() + mLen, 4);
			mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件" + QString::number(i + 1) + "在装置中的编号: " + QString::number(info.no) + "\r\n");
			mLen += 4;
			ba.clear();
			ba.append(buff.data() + mLen, 50);
			info.fileInfo = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + mLen, 50) + "\t文件" + QString::number(i + 1) + "故障概要描述信息: " + info.fileInfo + "\r\n");
			mLen += 50;
			files.append(info);
		}
	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}
