#include "iec103netapciwiscom.h"

IEC103NetApciWiscom::IEC103NetApciWiscom(const MyConfig& Config): IEC104Apci(Config)
{
	first = 0;
	length = 0;
	source_factory_addr = 0;
	memset(source_dev_addr, 0, sizeof(source_dev_addr));
	destination_factory_addr = 0;
	memset(destination_dev_addr, 0, sizeof(destination_dev_addr));
	memset(reserve, 0, sizeof(reserve));
}

IEC103NetApciWiscom::~IEC103NetApciWiscom()
{

}

bool IEC103NetApciWiscom::handle(const QByteArray& buff)
{
	int lengthlen = stringToInt(mConfig.lengthType);
	if(buff.count() < lengthlen + 13)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度不满15个字节");
		return false;
	}
	source_factory_addr = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t源厂站地址:" + QString::number(source_factory_addr) + "\r\n");
	mLen++;

	memcpy(source_dev_addr, buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t源设备地址:" + QString::number(source_dev_addr[1] * 0x100 + source_dev_addr[0]) + "\r\n");
	mLen += 2;

	destination_factory_addr = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t目的厂站地址:" + QString::number(destination_factory_addr) + "\r\n");
	mLen++;

	memcpy(destination_dev_addr, buff.data() + mLen, 2);
	mText.append(CharToHexStr(buff.data() + mLen, 2) + "\t目的设备地址:" + QString::number(destination_dev_addr[1] * 0x100 + destination_dev_addr[0]) + "\r\n");
	mLen += 2;

	reserve[0] = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t备用\r\n");
	mLen++;

	reserve[1] = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t备用\r\n");
	mLen++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103NetApciWiscom::showToText()
{
	QString text;
	text.append(mText);

	return text;
}

bool IEC103NetApciWiscom::createData(MyData& proData)
{
//	config.data += 0x68;
//	config.data += '\0';
//	config.data += '\0';
//	if(!control.createData(config))
//	{
//		return false;
//	}
	return true;
}
