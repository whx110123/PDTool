#include "iec103asdu104data.h"

IEC103Asdu104Data::IEC103Asdu104Data(const MyConfig& Config): IEC103AsduData(Config)
{

}

IEC103Asdu104Data::~IEC103Asdu104Data()
{

}

bool IEC103Asdu104Data::handle(const QByteArray& buff)
{
	if(mConfig.protocolName == IEC_103HUABEI)
	{
		//规约无此内容
	}
	else
	{
		rii = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
		mLen++;

		isLast = *(buff.data() + mLen) & 0x01;
		mText.append(CharToHexStr(buff.data() + mLen) + "\t后续位标志: " + QString(isLast ? "1 有后续帧" : "0 最后的帧") + "\r\n");
		mLen++;
	}

	if(mLen == buff.size())
	{
		return true;
	}
	fileIndex = charTouint(buff.data() + mLen, 4);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t起始传输位置: " + QString::number(fileIndex) + "\r\n");
	mLen += 4;

	fileData = buff.mid(mLen);
	mText.append(CharToHexStr(buff.data() + mLen, fileData.length()) + "\t文件数据: \r\n");
	mLen += fileData.length();

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}
