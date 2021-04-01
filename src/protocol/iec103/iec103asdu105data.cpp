#include "iec103asdu105data.h"

IEC103Asdu105Data::IEC103Asdu105Data(const MyConfig& Config): IEC103AsduData(Config)
{
	gbk = QTextCodec::codecForName("GB18030");
}

IEC103Asdu105Data::~IEC103Asdu105Data()
{

}

bool IEC103Asdu105Data::handle(const QByteArray& buff)
{
	if(mConfig.protocolName == IEC_103BAOXINNET_NW)
	{
		rii = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
		mLen++;

		flag = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t传送标识: " + QString::number(flag) + "\r\n");
		mLen++;

		QByteArray ba(buff.data() + mLen, 100);
		fileName = gbk->toUnicode(ba);
		mText.append(CharToHexStr(buff.data() + mLen, 100) + "\t文件名: " + fileName + "\r\n");
		mLen += 100;
		dt = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
		fileSize = charTouint(buff.data() + mLen, 4);
		mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t文件大小: " + QString::number(fileSize) + "\r\n");
		mLen += 4;
	}
	else
	{
		reportNum = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t故障报告文件个数 :" + QString::number(reportNum) + "\r\n");
		mLen++;

		for(int i = 0; i < reportNum; i++)
		{
			QByteArray ba(buff.data() + mLen, 100);
			fileName = gbk->toUnicode(ba);
			mText.append(CharToHexStr(buff.data() + mLen, 100) + "\t文件" + QString::number(i + 1) + "名称: " + fileName + "\r\n");
			mLen += 100;
			fileNames.append(fileName);
		}
		dt = charToDateTime(buff.data() + mLen, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + mLen, 7));
		mLen += 7;
	}

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}
