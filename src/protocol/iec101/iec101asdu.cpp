﻿#include "iec101asdu.h"
#include "iec101asdu11data.h"
#include "iec101asdu20data.h"
#include "iec101asdu30data.h"
#include "iec101asdu31data.h"
#include "iec101asdu32data.h"
#include "iec101asdu33data.h"
#include "iec101asdu34data.h"
#include "iec101asdu35data.h"
#include "iec101asdu36data.h"
#include "iec101asdu37data.h"
#include "iec101asdu38data.h"
#include "iec101asdu39data.h"
#include "iec101asdu40data.h"
#include "iec101asdu70data.h"
#include "iec101asdu100data.h"
#include "iec101asdu101data.h"
#include "iec101asdu102data.h"
#include "iec101asdu104data.h"
#include "iec101asdu105data.h"
#include "iec101asdu106data.h"
#include "iec101asdu111data.h"
#include "iec101asdu112data.h"
#include "iec101asdu113data.h"
#include "iec101asdu120data.h"
#include "iec101asdu121data.h"
#include "iec101asdu122data.h"
#include "iec101asdu123data.h"
#include "iec101asdu124data.h"
#include "iec101asdu125data.h"
#include "iec101asdu126data.h"

#include "iec104asdu43data.h"
#include "iec104asdu55data.h"
#include "iec104asdu58data.h"
#include "iec104asdu59data.h"
#include "iec104asdu60data.h"
#include "iec104asdu61data.h"
#include "iec104asdu62data.h"
#include "iec104asdu63data.h"
#include "iec104asdu64data.h"
#include "iec104asdu107data.h"
#include "iec104asdu116data.h"
#include "iec104asdu127data.h"
#include "iec104asdu137data.h"
#include "iec104asdu167data.h"

IEC101AsduData::IEC101AsduData(const MyConfig& Config): MyBase(Config)
{
	infaddr = 0;
}

IEC101AsduData::~IEC101AsduData()
{

}

bool IEC101AsduData::init(const QByteArray& buff)
{
	setDefault(buff);

	if(mConfig.infaddrlen > 0 && mConfig.infaddrlen < 4)
	{
		infaddr = charTouint(buff.data() + mLen, mConfig.infaddrlen);
		mText.append(CharToHexStr(buff.data() + mLen, mConfig.infaddrlen) + "\t信息元素地址:" + QString::number(infaddr));
		mLen += mConfig.infaddrlen;
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！信息体地址字节数错误");
		return false;
	}

	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	if(!handle(buff))
	{
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}

bool IEC101AsduData::init(const QByteArray& buff, uint addr)
{
	setDefault(buff);

	infaddr = addr;
	mText.append("\t信息元素地址:" + QString::number(infaddr));
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	if(!handle(buff))
	{
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}

bool IEC101AsduData::handle(const QByteArray& buff)
{
	return false;
}



IEC101Asdu::IEC101Asdu(const MyConfig& Config): MyBase(Config)
{
	type = 0;
	vsq = 0;
	memset(cot, 0, sizeof(cot));
	commonaddr = 0;


}

IEC101Asdu::~IEC101Asdu()
{
	qDeleteAll(datalist);
	datalist.clear();
}

bool IEC101Asdu::init(const QByteArray& buff)
{
	setDefault(buff);

	qDeleteAll(datalist);
	datalist.clear();

	if(2 + mConfig.cotlen + mConfig.comaddrlen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}

	type = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + typeToText() + "\r\n");
	mLen++;

	vsq = *(buff.data() + mLen);
	uchar sqflag = (vsq >> 7) & 0x01;
	uchar datanum = 0;
	if(type == 167)			//由于167号报文vsq为0
	{
		datanum = 1;
	}
	else
	{
		datanum = vsq & 0x7f;
	}
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + vsqToText() + "\r\n");
	mLen++;

	if(mConfig.cotlen == 1)
	{
		cot[0] = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t" + cotToText() + "\r\n");
		mLen++;
	}
	else if(mConfig.cotlen == 2)
	{
		cot[0] = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t" + cotToText() + "\r\n");
		mLen++;
		cot[1] = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen) + "\t源发站地址号:" + QString::number(cot[1]) + "\r\n");
		mLen++;
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！传送原因字节数错误");
		return false;
	}

	if(mConfig.comaddrlen == 1 || mConfig.comaddrlen == 2)
	{
		commonaddr = charTouint(buff.data() + mLen, mConfig.comaddrlen);
		mText.append(CharToHexStr(buff.data() + mLen, mConfig.comaddrlen) + "\t公共地址:" + QString::number(commonaddr) + "\r\n");
		mLen += mConfig.comaddrlen;
		mText.append("-----------------------------------------------------------------------------------------------\r\n");
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！公共地址字节数错误");
		return false;
	}

	uint dataaddr = 0;
	if(mConfig.infaddrlen > 0 && mConfig.infaddrlen < 4)
	{
		dataaddr = charTouint(buff.data() + mLen, mConfig.infaddrlen);
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！信息体地址字节数错误");
		return false;
	}
	for(int index = 0; index < datanum; index++)
	{
		IEC101AsduData *mdata = CreateAsduData(type);
		if(!mdata)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的asdu类型");
			return false;
		}
		datalist.append(mdata);
		mdata->asduType = type;
		mdata->mIndex = index;
		bool isOk;
		if(index == 0 || sqflag == 0)
		{
			isOk = mdata->init(buff.mid(mLen));
		}
		else
		{
			isOk = mdata->init(buff.mid(mLen), dataaddr + index);
		}
		mText.append(mdata->showToText());
		if(!isOk)
		{
			return false;
		}
		mLen += mdata->mLen;
	}
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	mRecvData.resize(mLen);
	return true;
}

bool IEC101Asdu::createData(MyData& proData)
{
	MyData tmp;
	tmp.getAttribute(proData);

	tmp.data += type;
	tmp.data += (type == 167 ? vsq : (vsq & 0x80 + datalist.count()));
	tmp.data += QByteArray((char *)cot, mConfig.cotlen);
	tmp.data += uintToBa(commonaddr, mConfig.comaddrlen);
	int index = 0;

	for(IEC101AsduData *mdata : qAsConst(datalist))
	{
		if(index > 0 && (vsq & 0x80))
		{
			tmp.sqFlag = SQ_NOADDR;
		}
		else
		{
			tmp.sqFlag = SQ_INF;
		}
		if(!mdata->createData(tmp))
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
			return false;
		}
		index++;
	}

	if(proData.reverse)
	{
		proData = tmp + proData;
	}
	else
	{
		proData = proData + tmp;
	}
	mSendData = proData.data;
	return true;

}

QString IEC101Asdu::typeToText()
{
	QString text = "类型标识ASDU" + QString::number(type) + "   ";
	switch(type)
	{
	case 1:
		text.append("单点信息");
		break;
	case 2:
		text.append("带时标的单点信息");
		break;
	case 3:
		text.append("双点信息");
		break;
	case 4:
		text.append("带时标的双点遥信");
		break;
	case 5:
		text.append("步位置(档位)信息");
		break;
	case 6:
		text.append("带时标的步位置信息");
		break;
	case 7:
		text.append("32比特串");
		break;
	case 8:
		text.append("带时标的32比特串");
		break;
	case 9:
		text.append("测量值, 规一化值");
		break;
	case 10:
		text.append("测量值，带时标的规一化值");
		break;
	case 11:
		text.append("测量值, 标度化值");
		break;
	case 12:
		text.append("测量值, 带时标的标度化值");
		break;
	case 13:
		text.append("测量值, 短浮点数");
		break;
	case 14:
		text.append("测量值, 带时标的短浮点数");
		break;
	case 15:
		text.append("累计量");
		break;
	case 16:
		text.append("带时标的累计量");
		break;
	case 17:
		text.append("带时标的继电保护设备事件");
		break;
	case 18:
		text.append("带时标的继电保护设备成组启动事件");
		break;
	case 19:
		text.append("带时标的继电保护设备成组输出电路信息");
		break;
	case 20:
		text.append("带变位检出的成组单点信息");
		break;
	case 21:
		text.append("测量值, 不带品质描述词的规一化值");
		break;
	case 30:
		text.append("带CP56Time2a时标的单点信息");
		break;
	case 31:
		text.append("带CP56Time2a时标的双点信息");
		break;
	case 32:
		text.append("带CP56Time2a时标的步位置信息");
		break;
	case 33:
		text.append("带CP56Time2a时标的32比特串");
		break;
	case 34:
		text.append("带CP56Time2a时标的测量值, 规一化值");
		break;
	case 35:
		text.append("带CP56Time2a时标的测量值, 标度化值");
		break;
	case 36:
		text.append("带CP56Time2a时标的测量值, 短浮点数");
		break;
	case 37:
		text.append("带CP56Time2a时标的累计量");
		break;
	case 38:
		text.append("带CP56Time2a时标的继电保护设备事件");
		break;
	case 39:
		text.append("带CP56Time2a时标的继电保护设备成组启动事件");
		break;
	case 40:
		text.append("带CP56Time2a时标的继电保护设备成组输出电路信息");
		break;
	case 43:
		text.append("文件传输(一键顺控扩展功能)");
		break;
	case 44:
		text.append("未定义，保留");
		break;
	case 45:
		text.append("单点命令");
		break;
	case 46:
		text.append("双点命令");
		break;
	case 47:
		text.append("步调节命令");
		break;
	case 48:
		text.append("设定值命令, 规一化值");
		break;
	case 49:
		text.append("设定值命令, 标度化值");
		break;
	case 50:
		text.append("设定值命令, 短浮点数");
		break;
	case 51:
		text.append("32比特串");
		break;
	case 55:
		text.append("序列控制命令交互(一键顺控扩展功能)");
		break;
	case 58:
		text.append("带CP56Time2a时标的单点命令");
		break;
	case 59:
		text.append("带CP56Time2a时标的双点命令");
		break;
	case 60:
		text.append("带CP56Time2a时标的步调节命令");
		break;
	case 61:
		text.append("带CP56Time2a时标的设定值命令, 规一化值");
		break;
	case 62:
		text.append("带CP56Time2a时标的设定值命令, 标度化值");
		break;
	case 63:
		text.append("带CP56Time2a时标的设定值命令, 短浮点数");
		break;
	case 64:
		text.append("带CP56Time2a时标的32比特串");
		break;
	case 70:
		text.append("初始化结束");
		break;
	case 100:
		text.append("总召唤命令");
		break;
	case 101:
		text.append("计数量召唤命令");
		break;
	case 102:
		text.append("读命令");
		break;
	case 103:
		text.append("时钟同步命令");
		break;
	case 104:
		text.append("测试命今");
		break;
	case 105:
		text.append("复位进程命令");
		break;
	case 106:
		text.append("延时获得命今");
		break;
	case 107:
		text.append("带CP56Time2a时标的测试命今");
		break;
	case 110:
		text.append("测量值参数, 规一化值");
		break;
	case 111:
		text.append("测量值参数, 标度化值");
		break;
	case 112:
		text.append("测量值参数, 短浮点数");
		break;
	case 113:
		text.append("参数激活");
		break;
	case 116:
		text.append("源端维护/南网顺控");
		break;
	case 120:
		text.append("文件淮备就绪");
		break;
	case 121:
		text.append("节淮备就绪");
		break;
	case 122:
		text.append("召唤目录, 选择文件, 召唤文件，召唤节");
		break;
	case 123:
		text.append("最后的节,最后的段");
		break;
	case 124:
		text.append("认可文件,认可节");
		break;
	case 125:
		text.append("段");
		break;
	case 126:
		text.append("目录");
		break;
	case 127:
		text.append("查询日志");
		break;
	case 137:
		text.append("计划曲线传送(南网扩展功能)");
		break;
	case 167:
		text.append("定值处理(扩展功能)");
		break;
	default:
		text.append("未知ASDU类型");
		break;
	}
	return text;
}

QString IEC101Asdu::vsqToText()
{
	QString text;
	text.append("可变结构限定词VSQ");
	text.append("\r\n\t数目(bit1-7):" + QString::number(vsq & 0x7f) + "   信息元素数量");
	text.append("\r\n\tSQ(bit8):" + QString::number(vsq & 0x80, 16).toUpper() + "   ");
	if(vsq & 0x80)
	{
		text.append("只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1");
	}
	else
	{
		text.append("每个信息元素都有独自的地址");
	}

	return text;
}

QString IEC101Asdu::cotToText()
{
	QString text = "传送原因COT(bit1-6):" + QString::number(cot[0] & 0x3f) + "   ";
	switch(cot[0] & 0x3f)
	{
	case 1:
		text.append("周期、循环上送");
		break;
	case 2:
		text.append("背景扫描，基于连续传送方式，用于监视方向，将被控站的过程信息去同步控制站的数据库，优先级较低");
		break;
	case 3:
		text.append("突发、自发");
		break;
	case 4:
		text.append("初始化");
		break;
	case 5:
		text.append("请求或被请求");
		break;
	case 6:
		text.append("激活");
		break;
	case 7:
		text.append("激活确认");
		break;
	case 8:
		text.append("停止激活");
		break;
	case 9:
		text.append("停止激活确认");
		break;
	case 10:
		text.append("激活终止");
		break;
	case 11:
		text.append("远方命令引起的返送信息");
		break;
	case 12:
		text.append("当地命令引起的返送信息");
		break;
	case 13:
		text.append("文件传输");
		break;
	case 20:
		text.append("响应站召唤");
		break;
	case 21:
		text.append("响应第1组召唤");
		break;
	case 22:
		text.append("响应第2组召唤");
		break;
	case 23:
		text.append("响应第3组召唤");
		break;
	case 24:
		text.append("响应第4组召唤");
		break;
	case 25:
		text.append("响应第5组召唤");
		break;
	case 26:
		text.append("响应第6组召唤");
		break;
	case 27:
		text.append("响应第7组召唤");
		break;
	case 28:
		text.append("响应第8组召唤");
		break;
	case 29:
		text.append("响应第9组召唤");
		break;
	case 30:
		text.append("响应第10组召唤");
		break;
	case 31:
		text.append("响应第11组召唤");
		break;
	case 32:
		text.append("响应第12组召唤");
		break;
	case 33:
		text.append("响应第13组召唤");
		break;
	case 34:
		text.append("响应第14组召唤");
		break;
	case 35:
		text.append("响应第15组召唤");
		break;
	case 36:
		text.append("响应第16组召唤");
		break;
	case 37:
		text.append("响应计数量(累积量)站(总)召唤");
		break;
	case 38:
		text.append("响应第1组计数量(累积量)召唤");
		break;
	case 39:
		text.append("响应第2组计数量(累积量)召唤");
		break;
	case 40:
		text.append("响应第3组计数量(累积量)召唤");
		break;
	case 41:
		text.append("响应第4组计数量(累积量)召唤");
		break;
	case 44:
		text.append("未知的类型标识，收到报文的类型标识不正确");
		break;
	case 45:
		text.append("未知的传送原因，收到报文的传送原因不正确");
		break;
	case 46:
		text.append("未知的应用服务数据单元公共地址，收到报文的公共地址不正确");
		break;
	case 47:
		text.append("未知的信息对象地址，收到报文的信息对象地址不正确");
		break;
	default:
		text.append("未知，无法识别当前的传送原因");
		break;
	}
	text.append("\r\n\tP/N(bit7):");
	if(cot[0] & 0x40)
	{
		text.append("40   否定确认");
	}
	else
	{
		text.append("0   肯定确认");
	}
	text.append("\r\n\tT(bit8):");
	if(cot[0] & 0x80)
	{
		text.append("80   试验状态");
	}
	else
	{
		text.append("0   未试验");
	}

	return text;
}

IEC101AsduData *IEC101Asdu::CreateAsduData(uchar type)
{
	IEC101AsduData *asdudata = NULL;
	switch(type)
	{
	case 1:
		asdudata = new IEC101Asdu1Data(mConfig);
		break;
	case 2:
		asdudata = new IEC101Asdu2Data(mConfig);
		break;
	case 3:
		asdudata = new IEC101Asdu3Data(mConfig);
		break;
	case 4:
		asdudata = new IEC101Asdu4Data(mConfig);
		break;
	case 5:
		asdudata = new IEC101Asdu5Data(mConfig);
		break;
	case 6:
		asdudata = new IEC101Asdu6Data(mConfig);
		break;
	case 7:
		asdudata = new IEC101Asdu7Data(mConfig);
		break;
	case 8:
		asdudata = new IEC101Asdu8Data(mConfig);
		break;
	case 9:
		asdudata = new IEC101Asdu9Data(mConfig);
		break;
	case 10:
		asdudata = new IEC101Asdu10Data(mConfig);
		break;
	case 11:
		asdudata = new IEC101Asdu11Data(mConfig);
		break;
	case 12:
		asdudata = new IEC101Asdu12Data(mConfig);
		break;
	case 13:
		asdudata = new IEC101Asdu13Data(mConfig);
		break;
	case 14:
		asdudata = new IEC101Asdu14Data(mConfig);
		break;
	case 15:
		asdudata = new IEC101Asdu15Data(mConfig);
		break;
	case 16:
		asdudata = new IEC101Asdu16Data(mConfig);
		break;
	case 17:
		asdudata = new IEC101Asdu17Data(mConfig);
		break;
	case 18:
		asdudata = new IEC101Asdu18Data(mConfig);
		break;
	case 19:
		asdudata = new IEC101Asdu19Data(mConfig);
		break;
	case 20:
		asdudata = new IEC101Asdu20Data(mConfig);
		break;
	case 21:
		asdudata = new IEC101Asdu21Data(mConfig);
		break;
	case 30:
		asdudata = new IEC101Asdu30Data(mConfig);
		break;
	case 31:
		asdudata = new IEC101Asdu31Data(mConfig);
		break;
	case 32:
		asdudata = new IEC101Asdu32Data(mConfig);
		break;
	case 33:
		asdudata = new IEC101Asdu33Data(mConfig);
		break;
	case 34:
		asdudata = new IEC101Asdu34Data(mConfig);
		break;
	case 35:
		asdudata = new IEC101Asdu35Data(mConfig);
		break;
	case 36:
		asdudata = new IEC101Asdu36Data(mConfig);
		break;
	case 37:
		asdudata = new IEC101Asdu37Data(mConfig);
		break;
	case 38:
		asdudata = new IEC101Asdu38Data(mConfig);
		break;
	case 39:
		asdudata = new IEC101Asdu39Data(mConfig);
		break;
	case 40:
		asdudata = new IEC101Asdu40Data(mConfig);
		break;
	case 43:
		asdudata = new IEC104Asdu43Data(mConfig);
		break;
	case 45:
		asdudata = new IEC101Asdu45Data(mConfig);
		break;
	case 46:
		asdudata = new IEC101Asdu46Data(mConfig);
		break;
	case 47:
		asdudata = new IEC101Asdu47Data(mConfig);
		break;
	case 48:
		asdudata = new IEC101Asdu48Data(mConfig);
		break;
	case 49:
		asdudata = new IEC101Asdu49Data(mConfig);
		break;
	case 50:
		asdudata = new IEC101Asdu50Data(mConfig);
		break;
	case 51:
		asdudata = new IEC101Asdu51Data(mConfig);
		break;
	case 55:
		asdudata = new IEC104Asdu55Data(mConfig);
		break;
	case 58:
		asdudata = new IEC104Asdu58Data(mConfig);
		break;
	case 59:
		asdudata = new IEC104Asdu59Data(mConfig);
		break;
	case 60:
		asdudata = new IEC104Asdu60Data(mConfig);
		break;
	case 61:
		asdudata = new IEC104Asdu61Data(mConfig);
		break;
	case 62:
		asdudata = new IEC104Asdu62Data(mConfig);
		break;
	case 63:
		asdudata = new IEC104Asdu63Data(mConfig);
		break;
	case 64:
		asdudata = new IEC104Asdu64Data(mConfig);
		break;
	case 70:
		asdudata = new IEC101Asdu70Data(mConfig);
		break;
	case 100:
		asdudata = new IEC101Asdu100Data(mConfig);
		break;
	case 101:
		asdudata = new IEC101Asdu101Data(mConfig);
		break;
	case 102:
		asdudata = new IEC101Asdu102Data(mConfig);
		break;
	case 103:
		asdudata = new IEC101Asdu103Data(mConfig);
		break;
	case 104:
		asdudata = new IEC101Asdu104Data(mConfig);
		break;
	case 105:
		asdudata = new IEC101Asdu105Data(mConfig);
		break;
	case 106:
		asdudata = new IEC101Asdu106Data(mConfig);
		break;
	case 107:
		asdudata = new IEC104Asdu107Data(mConfig);
		break;
	case 110:
		asdudata = new IEC101Asdu110Data(mConfig);
		break;
	case 111:
		asdudata = new IEC101Asdu111Data(mConfig);
		break;
	case 112:
		asdudata = new IEC101Asdu112Data(mConfig);
		break;
	case 113:
		asdudata = new IEC101Asdu113Data(mConfig);
		break;
	case 116:
		asdudata = new IEC104Asdu116Data(mConfig);
		break;
	case 120:
		asdudata = new IEC101Asdu120Data(mConfig);
		break;
	case 121:
		asdudata = new IEC101Asdu121Data(mConfig);
		break;
	case 122:
		asdudata = new IEC101Asdu122Data(mConfig);
		break;
	case 123:
		asdudata = new IEC101Asdu123Data(mConfig);
		break;
	case 124:
		asdudata = new IEC101Asdu124Data(mConfig);
		break;
	case 125:
		asdudata = new IEC101Asdu125Data(mConfig);
		break;
	case 126:
		asdudata = new IEC101Asdu126Data(mConfig);
		break;
	case 127:
		asdudata = new IEC104Asdu127Data(mConfig);
		break;
	case 137:
		asdudata = new IEC104Asdu137Data(mConfig);
		break;
	case 167:
		asdudata = new IEC104Asdu167Data(mConfig);
		break;
	default:
		break;
	}
	return asdudata;
}




