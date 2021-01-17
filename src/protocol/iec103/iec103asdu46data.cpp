#include "iec103asdu46data.h"

IEC103Asdu46Data::IEC103Asdu46Data()
{
	yx8 = 0;
	yx8flag = 0;
	qds = 0;
}

IEC103Asdu46Data::~IEC103Asdu46Data()
{

}

bool IEC103Asdu46Data::handle(const QByteArray& buff)
{
	yx8 = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t" + yx8ToText() + "\r\n");
	len += 2;

	yx8flag = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t" + yx8FlagToText() + "\r\n");
	len += 2;

	qds = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu46Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

QString IEC103Asdu46Data::yx8ToText()
{
	QString text = "8个双点遥信状态";
	for(int i = 0; i < 8; i ++)
	{
		text.append("\r\n\t" + QString::number((yx8 >> i * 2) & 0x03) + " ");
		switch((yx8 >> i * 2) & 0x03)
		{
		case 0:
			text.append("中间状态或不确定状态");
			break;
		case 1:
			text.append("分位");
			break;
		case 2:
			text.append("合位");
			break;
		case 3:
			text.append("中间状态或不确定状态");
			break;
		default:
			break;
		}
		text.append(" 对应INF:" + QString::number(inf + i));
	}
	return text;
}

QString IEC103Asdu46Data::yx8FlagToText()
{
	QString text = "8个双点遥信与上次查询的变化状态";
	for(int i = 0; i < 8; i ++)
	{
		text.append("\r\n\t" + QString::number((yx8flag >> i * 2) & 0x03) + " ");
		switch((yx8flag >> i * 2) & 0x03)
		{
		case 0:
			text.append("上次报告后未检出到状态变化");
			break;
		case 3:
			text.append("上次报告后检出到状态变化");
			break;
		default:
			text.append("未知状态变化");
			break;
		}
		text.append(" 对应INF:" + QString::number(inf + i));
	}
	return text;
}
