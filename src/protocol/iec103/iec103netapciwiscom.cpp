#include "iec103netapciwiscom.h"

IEC103NetApciWiscom::IEC103NetApciWiscom()
{
	masterState = STATE_INIT;
	first = 0;
	length = 0;
	source_factory_addr = 0;
	memset(source_dev_addr, 0, sizeof(source_dev_addr));
	destination_factory_addr = 0;
	memset(destination_dev_addr, 0, sizeof(destination_dev_addr));
	memset(reserve, 0, sizeof(reserve));

	mLengthType = mConfig.lengthType;
}

IEC103NetApciWiscom::~IEC103NetApciWiscom()
{

}

bool IEC103NetApciWiscom::handle(const QByteArray& buff)
{
	int lengthlen = stringToInt(mLengthType);
	if(buff.count() < lengthlen + 13)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度不满15个字节");
		return false;
	}
	source_factory_addr = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t源厂站地址:" + QString::number(source_factory_addr) + "\r\n");
	len++;

	memcpy(source_dev_addr, buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t源设备地址:" + QString::number(source_dev_addr[1] * 0x100 + source_dev_addr[0]) + "\r\n");
	len += 2;

	destination_factory_addr = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t目的厂站地址:" + QString::number(destination_factory_addr) + "\r\n");
	len++;

	memcpy(destination_dev_addr, buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t目的设备地址:" + QString::number(destination_dev_addr[1] * 0x100 + destination_dev_addr[0]) + "\r\n");
	len += 2;

	reserve[0] = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t备用\r\n");
	len++;

	reserve[1] = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t备用\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
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

bool IEC103NetApciWiscom::createData(IECDataConfig& config)
{
	config.data += 0x68;
	config.data += '\0';
	config.data += '\0';
	if(!control.createData(config))
	{
		return false;
	}
	return true;
}
