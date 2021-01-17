#include "measuredterminalasdu.h"

MTAsdu::MTAsdu()
{
	afn = 0;
	seq = 0;
	memset(pw, 0, sizeof(pw));
	delayTime = 0;
	flag = 0;
}

MTAsdu::~MTAsdu()
{
	qDeleteAll(datalist);
	datalist.clear();
}

bool MTAsdu::init(const QByteArray& buff)
{
	setDefault(buff);

	qDeleteAll(datalist);
	datalist.clear();

	if(buff.count() < 8)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}

	afn = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + afnToText() + "\r\n");
	len++;

	seq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + seqToText() + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	uchar pwFlag = (flag & PW_AVAILABLE) ? 1 : 0;
	uchar tpFlag = (flag & TP_AVAILABLE) ? 1 : 0;
	int index = 0;
	while(len < buff.length() - pwFlag * 16 - tpFlag * 5)
	{
		MTAsduData *mdata = new MTAsduData;
		if(!mdata)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！申请内存失败");
			return false;
		}
		mdata->flag = flag;
		mdata->index = index;
		if(!mdata->init(buff.mid(len)))
		{
			mText.append(mdata->showToText());
			delete mdata;
			mdata = NULL;
			return false;
		}
		datalist.append(mdata);
		mText.append(mdata->showToText());
		len += mdata->len;
		index++;
	}
	if(len != buff.length() - pwFlag * 16 - tpFlag * 5)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！用户数据报文长度错误");
		return false;
	}

	if(pwFlag)
	{
		memcpy(pw, buff.data() + len, 16);
		mText.append(CharToHexStr(buff.data() + len, 16) + "\t消息验证码PW\r\n");
		len += 16;
	}
	if(tpFlag)
	{
		dt = charToDateTime(buff.data() + len, 4, MYTIME1);
		mText.append(myTime1ToText(buff.data() + len, 4));
		len += 4;
		delayTime = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len) + "\t允许发送传输延时时间" + QString::number(delayTime) + "分钟\r\n");
		len++;
	}
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString MTAsdu::showToText()
{
	QString text = mText;
	return text;
}

bool MTAsdu::createData(IECDataConfig& config)
{

}

QString MTAsdu::afnToText()
{
	QString text = "应用层功能码AFN" + QString::number(afn) + "   ";
	switch(afn)
	{
	case 0:
		text.append("确认∕否定");
		break;
	case 2:
		text.append("链路接口检测");
		break;
	case 4:
		text.append("写参数");
		break;
	case 6:
		text.append("身份认证及密钥协商");
		break;
	case 10:
		text.append("读参数");
		break;
	case 12:
		text.append("读当前数据");
		break;
	case 13:
		text.append("读历史数据");
		break;
	case 14:
		text.append("读事件记录");
		break;
	case 15:
		text.append("文件传输");
		break;
	case 16:
		text.append("中继转发");
		break;
	case 18:
		text.append("读任务数据");
		break;
	case 19:
		text.append("读告警数据");
		break;
	case 20:
		text.append("级联命令");
		break;
	case 21:
		text.append("用户自定义数据");
		break;
	default:
		text.append("未知AFN类型");
		break;
	}
	return text;
}

QString MTAsdu::seqToText()
{
	QString text = "帧序列域SEQ:";

	text.append("\r\n\t帧时间标签有效位TpV(bit8):");
	if(seq & 0x80)
	{
		flag |= TP_AVAILABLE;
		text.append("80   表示带有时间标签Tp");
	}
	else
	{
		text.append("0   表示无时间标签Tp");
	}

	text.append("\r\n\t首帧标志FIR(bit7):");
	if(seq & 0x40)
	{
		text.append("40   为报文的第一帧");
	}
	else
	{
		text.append("0   非报文的第一帧");
	}

	text.append("\r\n\t末帧标志FIN(bit6):");
	if(seq & 0x20)
	{
		text.append("20   为报文的最后一帧");
	}
	else
	{
		text.append("0   非报文的最后一帧");
	}

	text.append("\r\n\t请求确认标志位CON(bit5):");
	if(seq & 0x10)
	{
		text.append("10   需要对该帧报文进行确认");
	}
	else
	{
		text.append("0   不需要对该帧报文进行确认");
	}
	text.append("\r\n\t启动帧序号PSEQ/响应帧序号RSEQ(bit1-4):" + QString::number(seq & 0x0f));


	return text;
}

