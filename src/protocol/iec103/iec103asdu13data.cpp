#include "iec103asdu13data.h"

IEC103Asdu13Data::IEC103Asdu13Data(const MyConfig& Config): IEC103AsduData(Config)
{
	gbk = QTextCodec::codecForName("GB18030");
}

IEC103Asdu13Data::~IEC103Asdu13Data()
{

}

bool IEC103Asdu13Data::handle(const QByteArray& buff)
{
	rii = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	mLen++;

	uchar waveFileNameLen;
	if(mConfig.protocolName == IEC_103BAOXINNET_NW)
	{
		waveFileNameLen = 128;
	}
	else
	{
		waveFileNameLen = 64;
	}

	QByteArray ba(buff.data() + mLen, waveFileNameLen);
	waveFileName = gbk->toUnicode(ba);
	mText.append(CharToHexStr(buff.data() + mLen, waveFileNameLen) + "\t不含扩展名的录波文件名:   " + waveFileName + "\r\n");
	mLen += waveFileNameLen;

	fileIndex = charTouint(buff.data() + mLen, 4);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t起始传输位置: " + QString::number(fileIndex) + "\r\n");
	mLen += 4;

	if(mConfig.protocolName == IEC_103BAOXINNET_NW)
	{
		//南网无此部分
	}
	else
	{
		no = charTouint(buff.data() + mLen, 4);
		mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t录波文件在装置中的编号: " + QString::number(no) + "\r\n");
		mLen += 4;
	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}
