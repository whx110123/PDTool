#include "iec103asdu105data.h"

IEC103Asdu105Data::IEC103Asdu105Data()
{
	gbk = QTextCodec::codecForName("GB18030");
}

IEC103Asdu105Data::~IEC103Asdu105Data()
{

}

bool IEC103Asdu105Data::handle(const QByteArray& buff)
{
	if(protocolName == IEC_103BAOXINNET_NW)
	{
		rii = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
		len++;

		flag = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\t传送标识: " + QString::number(flag) + "\r\n");
		len++;

		QByteArray ba(buff.data() + len, 100);
		fileName = gbk->toUnicode(ba);
		mText.append(CharToHexStr(buff.data() + len, 100) + "\t文件名: " + fileName + "\r\n");
		len += 100;
		dt = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, 7));
		len += 7;
		fileSize = charTouint(buff.data() + len, 4);
		mText.append(CharToHexStr(buff.data() + len, 4) + "\t文件大小: " + QString::number(fileSize) + "\r\n");
		len += 4;
	}
	else
	{
		reportNum = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\t故障报告文件个数 :" + QString::number(reportNum) + "\r\n");
		len++;

		for(int i = 0; i < reportNum; i++)
		{
			QByteArray ba(buff.data() + len, 100);
			fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + len, 100) + "\t文件" + QString::number(i + 1) + "名称: " + fileName + "\r\n");
			len += 100;
			fileNames.append(fileName);
		}
		dt = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, 7));
		len += 7;
	}

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}
