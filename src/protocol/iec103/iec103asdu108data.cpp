#include "iec103asdu108data.h"

IEC103Asdu108Data::IEC103Asdu108Data(const MyConfig& Config): IEC103AsduData(Config)
{

}

IEC103Asdu108Data::~IEC103Asdu108Data()
{

}

bool IEC103Asdu108Data::handle(const QByteArray& buff)
{
	rii = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	mLen++;

	flag = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t确认标志: " + QString::number(flag) + "\r\n");
	mLen++;

	fileIndex = charTouint(buff.data() + mLen, 4);
	mText.append(CharToHexStr(buff.data() + mLen, 4) + "\t已经接收的有效长度: " + QString::number(fileIndex) + "\r\n");
	mLen += 4;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}
