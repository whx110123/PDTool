﻿#include "measuredterminalasdu.h"

MTAsdu::MTAsdu(const MyConfig& Config): MyBase(Config)
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
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}

	afn = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + afnToText() + "\r\n");
	mLen++;

	seq = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + seqToText() + "\r\n");
	mLen++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	uchar pwFlag = (flag & PW_AVAILABLE) ? 1 : 0;
	uchar tpFlag = (flag & TP_AVAILABLE) ? 1 : 0;
	int index = 0;
	while(mLen < buff.length() - pwFlag * 16 - tpFlag * 5)
	{
		MTAsduData *mdata = new MTAsduData(mConfig);
		if(!mdata)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！申请内存失败");
			return false;
		}
		datalist.append(mdata);
		mdata->flag = flag;
		mdata->afn = afn;
		mdata->mIndex = index++;
		if(!mdata->init(buff.mid(mLen)))
		{
			mText.append(mdata->showToText());
			return false;
		}
		mText.append(mdata->showToText());
		mLen += mdata->mLen;
	}

	if(pwFlag)
	{
		memcpy(pw, buff.data() + mLen, 16);
		mText.append(CharToHexStr(buff.data() + mLen, 16) + "\t消息验证码PW\r\n");
		mLen += 16;
	}
	if(tpFlag)
	{
		dt = charToDateTime(buff.data() + mLen, 4, MYTIME1);
		mText.append(myTime1ToText(buff.data() + mLen, 4));
		mLen += 4;
		delayTime = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t允许发送传输延时时间" + QString::number(delayTime) + "分钟\r\n");
		mLen++;
	}
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
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

