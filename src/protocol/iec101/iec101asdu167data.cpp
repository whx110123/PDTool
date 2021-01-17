#include "iec101asdu167data.h"

IEC101Asdu167Data::IEC101Asdu167Data()
{
	ctrl = 0;
	memset(devaddr, 0, sizeof(devaddr));
	iec103len = 0;
}

IEC101Asdu167Data::~IEC101Asdu167Data()
{

}

bool IEC101Asdu167Data::init(const QByteArray& buff)
{
	setDefault(buff);

	ctrl = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + ctrlToText() + "\r\n");
	len++;

	memcpy(devaddr, buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len) + "\t保护装置地址L:" + QString::number(devaddr[0]) + "\r\n");
	len++;
	mText.append(CharToHexStr(buff.data() + len) + "\t保护装置地址H:" + QString::number(devaddr[1]) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	iec103len = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\tIEC103数据长度:" + QString::number(iec103len) + "\r\n");
	len++;

	asdu.mCotlen = 1;
	asdu.mComaddrlen = 1;

	if(!asdu.init(buff.mid(len, iec103len)))
	{
		return false;
	}
	len += asdu.len;
	if(asdu.len != iec103len)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}


QString IEC101Asdu167Data::showToText()
{
	QString text = mText;
	text.append(asdu.showToText());
	return text;
}

bool IEC101Asdu167Data::createData(IECDataConfig& config)
{
	if(mInfaddrlen != 3)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！167号报文信息体地址长度错误");
		return false;
	}
	config.data += '\0';
	config.data.append(uintToBa(config.iec103config->devaddr, 2));
	if(config.isMaster)
	{
		config.iec103config->data.clear();
		asdu.mCotlen = 1;
		asdu.mComaddrlen = 1;
		if(!asdu.createData(*config.iec103config))
		{
			return false;
		}
		config.data += (uchar)config.iec103config->data.size();
		config.data.append(config.iec103config->data);
	}

	return true;


}

QString IEC101Asdu167Data::ctrlToText()
{
	QString text = "保护信息传输控制字节，A/S(bit8):" + QString::number(ctrl & 0x80, 16).toUpper() + " ";
	uchar datanum = ctrl & 0x7f;
	if(ctrl & 0x80)
	{
		text.append("有后续帧");
	}
	else
	{
		text.append("无后续帧");
	}
	text.append("当前帧号(bit1-7):" + QString::number(datanum));
	return text;
}
