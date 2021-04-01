#include "iec103asdu.h"
#include "iec103asdu1data.h"
#include "iec103asdu2data.h"
#include "iec103asdu6data.h"
#include "iec103asdu7data.h"
#include "iec103asdu8data.h"
#include "iec103asdu10data.h"
#include "iec103asdu21data.h"
#include "iec103asdu23data.h"
#include "iec103asdu24data.h"
#include "iec103asdu26data.h"
#include "iec103asdu27data.h"
#include "iec103asdu28data.h"
#include "iec103asdu29data.h"
#include "iec103asdu30data.h"
#include "iec103asdu36data.h"
#include "iec103asdu40data.h"
#include "iec103asdu41data.h"
#include "iec103asdu42data.h"
#include "iec103asdu43data.h"
#include "iec103asdu44data.h"
#include "iec103asdu46data.h"
#include "iec103asdu47data.h"
#include "iec103asdu50data.h"
#include "iec103asdu51data.h"
#include "iec103asdu88data.h"
#include "iec103asdu220data.h"
#include "iec103asdu221data.h"
#include "iec103asdu222data.h"
#include "iec103asdu223data.h"
#include "iec103asdu224data.h"
#include "iec103asdu225data.h"
#include "iec103asdu226data.h"
#include "iec103asdu227data.h"
#include "iec103asdu4data.h"
#include "iec103asdu5data.h"
#include "iec103asdu11data.h"
#include "iec103asdu20data.h"
#include "iec103asdu45data.h"
#include "iec103asdu32data.h"
#include "iec103asdu33data.h"
#include "iec103asdu34data.h"
#include "iec103asdu35data.h"
#include "iec103asdu37data.h"
#include "iec103asdu38data.h"
#include "iec103asdu39data.h"
#include "iec103asdu48data.h"
#include "iec103asdu64data.h"
#include "iec103asdu65data.h"
#include "iec103asdu66data.h"
#include "iec103asdu67data.h"
#include "iec103asdu12data.h"
#include "iec103asdu108data.h"
#include "iec103asdu107data.h"
#include "iec103asdu106data.h"
#include "iec103asdu103data.h"
#include "iec103asdu102data.h"
#include "iec103asdu18data.h"
#include "iec103asdu17data.h"
#include "iec103asdu16data.h"
#include "iec103asdu14data.h"
#include "iec103asdu13data.h"


IEC103AsduData::IEC103AsduData(const MyConfig& Config): MyBase(Config)
{
	asduType = 0;
	fun = 0;
	inf = 0;
	mMasterState = STATE_NORMAL;
}

IEC103AsduData::~IEC103AsduData()
{

}

bool IEC103AsduData::init(const QByteArray& buff)
{
	setDefault(buff);

	fun = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + funToText() + "\r\n");
	mLen++;

	inf = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + infToText() + "\r\n");
	mLen++;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	if(!handle(buff))
	{
		return false;
	}
	return true;
}

bool IEC103AsduData::init(const QByteArray& buff, uchar ch_fun)
{
	setDefault(buff);

	fun = ch_fun & 0xff;

	inf = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + infToText() + "\r\n");
	mLen++;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	if(!handle(buff))
	{
		return false;
	}
	return true;
}

bool IEC103AsduData::init(const QByteArray& buff, uchar ch_fun, uchar ch_inf)
{
	setDefault(buff);

	fun = ch_fun & 0xff;
	inf = ch_inf & 0xff;
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	if(!handle(buff))
	{
		return false;
	}
	return true;
}

bool IEC103AsduData::handle(const QByteArray& buff)
{
	return false;
}

QString IEC103AsduData::funToText()
{
	QString text = "FUN:" + QString::number(fun) + " ";
	switch(fun)
	{
	case 251:
		text.append("二次设备运行状态（分:检修 | 合:正常）（保信规约专用），此时INF表示装置地址");
		break;
	case 252:
		text.append("装置定值变化（保信规约专用），此时INF表示装置地址");
		break;
	case 253:
		text.append("二次设备通信状态（分:断 | 合:通）（保信规约专用），此时INF表示装置地址");
		break;
	case 254:
		text.append("通用分类功能类型GEN");
		break;
	case 255:
		text.append("全局功能类型GLB");
		break;
	default:
		break;
	}
	return text;
}


QString IEC103AsduData::infToText()
{
	QString text = "INF:" + QString::number(inf) + " ";
	if(fun == 254)
	{
		switch(inf)
		{
		case 240:
			text.append("读所有被定义组的标题");
			break;
		case 241:
			text.append("读一个组的全部条目的值或属性");
			break;
		case 243:
			text.append("读单个条目的目录");
			break;
		case 244:
			text.append("读单个条目的值或属性");
			break;
		case 245:
			text.append("通用分类数据的总查询(总召唤) 主站发出或子站中止");
			break;
		case 248:
			text.append("写条目");
			break;
		case 249:
			text.append("带确认的写条目");
			break;
		case 250:
			text.append("带执行的写条目");
			break;
		case 251:
			text.append("带中止的写条目");
			break;
		default:
			break;
		}
	}
	if(mConfig.protocolName == IEC_103BAOXINNET_NW)
	{
		if(fun == 255)
		{
			switch(asduType)
			{
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
				switch(inf)
				{
				case 0:
					text.append("从保信子站本地调录波列表");
					break;
				case 1:
					text.append("直接从保护装置或录波器调录波列表");
					break;
				default:
					break;
				}
				break;
			case 20:
				switch(inf)
				{
				case 19:
					text.append("复归");
					break;
				default:
					break;
				}
				break;
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 107:
			case 108:
				switch(inf)
				{
				case 0:
					text.append("不指定文件类型");
					break;
				case 1:
					text.append("系统文件(SVG,CIM)");
					break;
				case 2:
					text.append("子站日志文件");
					break;
				case 3:
					text.append("子站配置文件");
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}

		}
	}
	else if(mConfig.protocolName == IEC_103BAOXINNET)
	{
		if(fun == 162)
		{
			switch(asduType)
			{
			case 15:
				switch(inf)
				{
				case 0:
					text.append("从子站本地调录波文件列表");
					break;
				case 1:
					text.append("从子站本地调简化录波列表");
					break;
				case 2:
					text.append("直接从装置调录波文件列表");
					break;
				default:
					break;
				}
				break;
			case 16:
				switch(inf)
				{
				case 0:
					text.append("子站本地召唤录波文件列表回应");
					break;
				case 1:
					text.append("子站本地调简化录波列表回应");
					break;
				case 2:
					text.append("从装置召唤录波文件列表回应");
					break;
				default:
					break;
				}
				break;
			case 101:
				switch(inf)
				{
				case 0:
					text.append("调通用文件列表");
					break;
				default:
					break;
				}
				break;
			case 102:
				switch(inf)
				{
				case 0:
					text.append("调通用文件列表回应");
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}

		}
		else if(fun == 163)
		{
			switch(asduType)
			{
			case 13:
				switch(inf)
				{
				case 0:
					text.append("从子站本地调录波文件");
					break;
				case 1:
					text.append("从子站本地调简化录波文件");
					break;
				case 2:
					text.append("直接从装置调录波文件");
					break;
				default:
					break;
				}
				break;
			case 14:
				switch(inf)
				{
				case 0:
					text.append("从子站本地调录波文件回应");
					break;
				case 1:
					text.append("从子站本地调简化录波文件回应");
					break;
				case 2:
					text.append("从装置调录波文件回应");
					break;
				default:
					break;
				}
				break;
			case 103:
				switch(inf)
				{
				case 0:
					text.append("调通用文件");
					break;
				default:
					break;
				}
				break;
			case 104:
				switch(inf)
				{
				case 0:
					text.append("调通用文件回应");
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		else if(fun == 255)
		{
			switch(asduType)
			{
			case 17:
			case 18:
				switch(inf)
				{
				case 0:
					text.append("召唤子站本地保存的历史事件");
					break;
				case 1:
					text.append("直接对装置召唤的历史事件");
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

	}
	return text;
}

IEC103Asdu::IEC103Asdu(const MyConfig& Config): MyBase(Config)
{
	type = 0;
	vsq = 0;
	cot = 0;
	commonaddr = 0;
//	sqflag = 0;
//	datanum = 0;
	mMasterState = STATE_NORMAL;
	endflag = 0;
	end = 0;
}

IEC103Asdu::~IEC103Asdu()
{
	qDeleteAll(datalist);
	datalist.clear();
}

bool IEC103Asdu::init(const QByteArray& buff)
{
	setDefault(buff);

	qDeleteAll(datalist);
	datalist.clear();
	if(buff.count() < 4)
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度小于4");
		return false;
	}

	type = *(buff.data() + mLen);
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + typeToText() + "\r\n");
	mLen++;

	vsq = *(buff.data() + mLen);
	uchar sqflag = (vsq >> 7) & 0x01;
	uchar datanum = vsq & 0x7f;
	mText.append(CharToHexStr(buff.data() + mLen) + "\t" + vsqToText() + "\r\n");
	mLen++;

	if(mConfig.cotlen > 0)
	{
		cot = *(buff.data() + mLen);
		mText.append(CharToHexStr(buff.data() + mLen, mConfig.cotlen) + "\t" + cotToText() + "\r\n");
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！传送原因字节数错误");
		return false;
	}
	mLen += mConfig.cotlen;

	commonaddr = charTouint(buff.data() + mLen, mConfig.comaddrlen);
	if(mConfig.comaddrlen == 1)
	{
		mText.append(CharToHexStr(buff.data() + mLen) + "\t公共地址:" + QString::number(commonaddr & 0xff) + "\r\n");
	}
	else if(mConfig.comaddrlen == 2)
	{
		mText.append(CharToHexStr(buff.data() + mLen) + "\t公共地址低位:" + QString::number(commonaddr & 0xff) + "\r\n");
		mText.append(CharToHexStr(buff.data() + mLen + 1) + "\t公共地址高位:" + QString::number((commonaddr >> 8) & 0xff) + " 装置地址\r\n");
	}
	else
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！公共地址字节数错误");
		return false;
	}
	mLen += mConfig.comaddrlen;

	uchar fun = *(buff.data() + mLen);
	uchar inf = *(buff.data() + mLen + 1);;
	for(int index = 0; index < datanum; index++)
	{
		IEC103AsduData *mdata = CreateAsduData(type);
		if(!mdata)
		{
			mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的asdu类型");
			return false;
		}
		mdata->asduType = type;
		mdata->mIndex = index;
		bool isOk = false;
		if(index == 0)
		{
			isOk = mdata->init(buff.mid(mLen));
		}
		else if(sqflag == 1)
		{
			int sq = 0;
			switch(type)
			{
			case 40:
			case 41:
			case 42:
			case 43:
				if(mConfig.protocolName == IEC_103XUJINET)
				{
					sq = 1;
				}
				break;
			case 45:
			case 47:
			case 50:
			case 51:
				sq = 1;
				break;
			default:
				break;
			}
			if(sq == 0)
			{
				isOk = mdata->init(buff.mid(mLen));
			}
			else
			{
				isOk = mdata->init(buff.mid(mLen), fun);
			}
		}
		else
		{
			int k = 1;
			switch(type)
			{
			case 3:
			case 9:
			case 32:
			case 33:
			case 34:
			case 35:
				k = 0;
				break;
			case 44:
				k = 16;
				break;
			default:
				break;
			}
			isOk = mdata->init(buff.mid(mLen), fun, (uchar)(inf + index * k));
		}
		if(!isOk)
		{
			mText.append(mdata->showToText());
			delete mdata;
			mdata = NULL;
			return false;
		}
		datalist.append(mdata);
		mLen += mdata->mLen;
	}

	if(endflag != IEC103END_NO)
	{
		end = *(buff.data() + mLen);
		mLen++;
	}
	if(mLen > buff.length())
	{
		mError = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(mLen).arg(buff.length()));
		return false;
	}
	return true;
}

QString IEC103Asdu::showToText()
{
	QString text = mText;
	for(IEC103AsduData *mdata : datalist)
	{
		text.append(mdata->showToText());
	}
	if(endflag != IEC103END_NO)
	{
		text.append(CharToHexStr(end) + "\t" + endToText() + QString::number(end) + "\r\n");
	}
	return text;
}

bool IEC103Asdu::createData(MyData& proData)
{
//	qDeleteAll(datalist);
//	datalist.clear();

//	if(config.isMaster)
//	{
//		config.data += config.asdutype;
//		config.data += config.vsq;
//		config.data += config.cot;
//		config.data += (char)(config.devaddr & 0xff);
//		config.data += config.fun;
//		for(int i = 0; i < (config.vsq & 0x7f); i++)
//		{
//			IEC103AsduData *newdata = CreateAsduData(config.asdutype);
//			if(!newdata)
//			{
//				error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！对此asdu类型未完成报文生成");
//				return false;
//			}
//			newdata->index = i;
//			datalist.append(newdata);
//			if(!newdata->createData(config))
//			{
//				return false;
//			}
//		}

//	}
//	else
//	{
//		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
//		return false;
//	}
	//	config.data += config.asdutype;
	//	config.data += config.vsq;
	//	config.data += config.cot;
	//	config.data += '\0';
	//	config.data += uintToBa(App::IEC_COMADDR,2);
	//	config.isfirst = true;
	//	for(int i = 0;i<(config.vsq&0x7f);i++)
	//	{
	//		IEC103asdudata *newdata = CreateAsduData(config.asdutype);
	//		newdata->createData(config);
	//		datalist.append(newdata);
	//	}

	return true;
}

QString IEC103Asdu::typeToText()
{
	QString text = "类型标识ASDU" + QString::number(type) + "   ";
	endflag = IEC103END_NO;
	switch(type)
	{
	case 1:
		text.append("带时标的报文");
		endflag = IEC103END_SIN;
		break;
	case 2:
		text.append("具有相对时间的带时标的报文");
		endflag = IEC103END_SIN;
		break;
	case 3:
		text.append("被测值I");
		break;
	case 4:
		text.append("具有相对时间的带时标的被测值");
		break;
	case 5:
		text.append("标识");
		break;
	case 6:
		text.append("时间同步");
		break;
	case 7:
		text.append("总查询(总召唤)");
		endflag = IEC103END_SCN;
		break;
	case 8:
		text.append("总查询(总召唤)终止");
		endflag = IEC103END_SCN;
		break;
	case 9:
		text.append("被测值II");
		break;
	case 10:
		text.append("通用分类数据");
		break;
	case 11:
		text.append("通用分类标识");
		break;
	case 12:
		text.append("简要录波报告(保信规约专用)");
		break;
	case 13:
		text.append("召唤录波文件(保信规约专用)");
		break;
	case 14:
		text.append("上送录波文件(保信规约专用)");
		break;
	case 15:
		text.append("召唤录波文件列表(保信规约专用)");
		break;
	case 16:
		text.append("上送录波文件列表(保信规约专用)");
		break;
	case 17:
		text.append("召唤装置故障历史信息(保信规约专用)");
		break;
	case 18:
		text.append("装置故障历史信息(保信规约专用)");
		break;
	case 20:
		text.append("一般命令");
		endflag = IEC103END_RII;
		break;
	case 21:
		text.append("通用分类命令");
		break;
	case 23:
		text.append("被记录的扰动表");
		break;
	case 24:
		text.append("扰动数据传输的命令");
		break;
	case 25:
		text.append("扰动数据传输的认可");
		break;
	case 26:
		text.append("扰动数据传输准备就绪");
		break;
	case 27:
		text.append("被记录的通道传输准备就绪");
		break;
	case 28:
		text.append("带标志的状态变位传输准备就绪");
		break;
	case 29:
		text.append("传送带标志的状态变位");
		break;
	case 30:
		text.append("传送扰动值");
		break;
	case 31:
		text.append("传送结束");
		break;
	case 32:
		text.append("带时标的被测值III");
		break;
	case 33:
		text.append("带时标的被测值IV");
		break;
	case 34:
		text.append("带时标的向量被测值V");
		break;
	case 35:
		text.append("带时标的向量被测值VI");
		break;
	case 36:
		text.append("电能脉冲计数量");
		endflag = IEC103END_RII;
		break;
	case 37:
		text.append("带时标的电能脉冲计数量");
		endflag = IEC103END_RII;
		break;
	case 38:
		text.append("步位置信息");
		break;
	case 39:
		text.append("带时标的步位置信息");
		break;
	case 40:
		text.append("单点状态信息");
		endflag = IEC103END_SIN;
		break;
	case 41:
		text.append("带时标的单点状态信息");
		endflag = IEC103END_SIN;
		break;
	case 42:
		text.append("双点状态信息");
		endflag = IEC103END_SIN;
		break;
	case 43:
		text.append("带时标的双点状态信息");
		endflag = IEC103END_SIN;
		break;
	case 44:
		text.append("单点状态和状态变位检出");
		endflag = IEC103END_SIN;
		break;
	case 45:
		text.append("带时标的单点状态和状态变位检出");
		endflag = IEC103END_SIN;
		break;
	case 46:
		text.append("双点状态和状态变位检出");
		endflag = IEC103END_SIN;
		break;
	case 47:
		text.append("带时标的双点状态和状态变位检出");
		endflag = IEC103END_SIN;
		break;
	case 48:
		text.append("水位");
		endflag = IEC103END_RII;
		break;
	case 50:
		text.append("被测值VII");
		break;
	case 51:
		text.append("变化的被测值VII");
		break;
	case 64:
		text.append("控制断路器命令");
		endflag = IEC103END_RII;
		break;
	case 65:
		text.append("升降命令");
		endflag = IEC103END_RII;
		break;
	case 66:
		text.append("设定命令");
		endflag = IEC103END_RII;
		break;
	case 67:
		text.append("控制命令");
		endflag = IEC103END_RII;
		break;
	case 88:
		text.append("电能脉冲量召唤或冻结");
		endflag = IEC103END_RII;
		break;
	case 101:
		text.append("召唤一般文件列表(保信规约专用)");
		break;
	case 102:
		text.append("上送一般文件列表(保信规约专用)");
		break;
	case 103:
		text.append("召唤一般文件内容(保信规约专用)");
		break;
	case 104:
		text.append("上送一般文件内容(保信规约专用)");
		break;
	case 105:
		if(mConfig.protocolName == IEC_103BAOXINNET_NW)
		{
			text.append("下传一般文件的基本信息(南网保信103)");
		}
		else
		{
			text.append("上送故障归档报告(保信规约专用)");
		}
		break;
	case 106:
		text.append("下传一般文件基本信息的确认(南网保信103)");
		break;
	case 107:
		text.append("下传一般文件的内容(南网保信103)");
		break;
	case 108:
		text.append("下传一般文件内容的确认(南网保信103)");
		break;
	case 220:
		text.append("通用历史数据查询（金智103专用）");
		endflag = IEC103END_RII;
		break;
	case 221:
		text.append("文件目录召唤（金智103专用）");
		break;
	case 222:
		text.append("文件目录响应（金智103专用）");
		break;
	case 223:
		text.append("文件准备就绪（金智103专用）");
		break;
	case 224:
		text.append("节准备就绪帧（金智103专用）");
		break;
	case 225:
		text.append("段的发送帧（金智103专用）");
		break;
	case 226:
		text.append("后的段、最后的节表示帧（金智103专用）");
		break;
	case 227:
		text.append("文件确认或节确认帧（金智103专用）");
		break;
	case 228:
		text.append("遥控校验命令（金智103专用）");
		break;
	case 229:
		text.append("遥控校验结果（金智103专用）");
		break;
	default:
		text.append("未知ASDU类型，无法继续解析");
		break;
	}
	return text;
}

QString IEC103Asdu::vsqToText()
{
	QString text;
	text.append("可变结构限定词VSQ");
	text.append("\r\n\t数目(bit1-7):" + QString::number(vsq & 0x7f) + "   信息元素数量");
	text.append("\r\n\tSQ(bit8):" + QString::number(vsq & 0x80, 16).toUpper() + "   ");
	if(vsq & 0x80)
	{
		text.append("每个信息元素都有独自的地址");
	}
	else
	{
		text.append("只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1");
	}
	return text;
}

QString IEC103Asdu::cotToText()
{
	QString text = "传送原因COT:" + QString::number(cot) + "   ";
	switch(cot)
	{
	case 1:
		text.append("自发(突发)");
		break;
	case 2:
		text.append("循环");
		break;
	case 3:
		text.append("复位帧计数位(FCB)");
		break;
	case 4:
		text.append("复位通信单元(CU)");
		break;
	case 5:
		text.append("启动/重新启动");
		break;
	case 6:
		text.append("电源合上");
		break;
	case 7:
		text.append("测试模式，检修状态下的突变");
		break;
	case 8:
		text.append("时间同步 主站启动或子站响应");
		break;
	case 9:
		text.append("总查询(总召唤) 主站启动或子站响应");
		break;
	case 10:
		text.append("总查询(总召唤)终止");
		break;
	case 11:
		text.append("当地操作");
		break;
	case 12:
		text.append("远方操作");
		break;
	case 20:
		text.append("一般命命令 主站发出或子站肯定认可");
		break;
	case 21:
		text.append("一般命令的否定认可");
		break;
	case 31:
		text.append("扰动数据的传送");
		break;
	case 40:
		text.append("通用分类写命令 主站发出或子站肯定认可");
		break;
	case 41:
		text.append("通用分类写命令的否定认可");
		break;
	case 42:
		text.append("对通用分类读命令 主站发出或子站有效数据响应");
		break;
	case 43:
		text.append("对通用分类读命令无效数据响应");
		break;
	case 44:
		text.append("通用分类写确认");
		break;
	case 45:
		text.append("读列表 主站发出或子站肯定认可(保信规约专用)");
		break;
	case 46:
		text.append("读内容 主站发出或子站肯定认可(保信规约专用)");
		break;
	case 128:
		text.append("历史数据查询(金智103专用)");
		break;
	case 129:
		text.append("历史数据查询结束(金智103专用)");
		break;
	case 130:
		text.append("文件传输(金智103专用)");
		break;
	case 252:
		text.append("取消操作(保信规约专用)");
		break;
	default:
		text.append("未知，无法识别当前的传送原因");
		break;
	}
	return text;
}

QString IEC103Asdu::endToText()
{
	QString text;
	switch(endflag)
	{
	case IEC103END_RII:
		text.append("返回信息标识符RII:");
		break;
	case IEC103END_SCN:
		text.append("扫描序号SCN:");
		break;
	case IEC103END_SIN:
		text.append("附加信息SIN:");
		if(mConfig.protocolName == IEC_103BAOXINNET_NW)
		{
			text.append(fptToText(endflag));
		}
		break;
	default:
		break;
	}
	return text;
}

IEC103AsduData *IEC103Asdu::CreateAsduData(uchar type)
{
	IEC103AsduData *asdudata = NULL;
	switch(type)
	{
	case 1:
		asdudata = new IEC103Asdu1Data(mConfig);
		break;
	case 2:
		asdudata = new IEC103Asdu2Data(mConfig);
		break;
	case 3:
		asdudata = new IEC103Asdu50Data(mConfig);
		break;
	case 4:
		asdudata = new IEC103Asdu4Data(mConfig);
		break;
	case 5:
		asdudata = new IEC103Asdu5Data(mConfig);
		break;
	case 6:
		asdudata = new IEC103Asdu6Data(mConfig);
		break;
	case 7:
		asdudata = new IEC103Asdu7Data(mConfig);
		break;
	case 8:
		asdudata = new IEC103Asdu8Data(mConfig);
		break;
	case 9:
		asdudata = new IEC103Asdu50Data(mConfig);
		break;
	case 10:
		asdudata = new IEC103Asdu10Data(mConfig);
		break;
	case 11:
		asdudata = new IEC103Asdu11Data(mConfig);
		break;
	case 12:
		asdudata = new IEC103Asdu12Data(mConfig);
		break;
	case 13:
		asdudata = new IEC103Asdu13Data(mConfig);
		break;
	case 14:
		asdudata = new IEC103Asdu14Data(mConfig);
		break;
	case 15:
		asdudata = new IEC103Asdu15Data(mConfig);
		break;
	case 16:
		asdudata = new IEC103Asdu16Data(mConfig);
		break;
	case 17:
		asdudata = new IEC103Asdu17Data(mConfig);
		break;
	case 18:
		asdudata = new IEC103Asdu18Data(mConfig);
		break;
	case 20:
		asdudata = new IEC103Asdu20Data(mConfig);
		break;
	case 21:
		asdudata = new IEC103Asdu21Data(mConfig);
		break;
	case 23:
		asdudata = new IEC103Asdu23Data(mConfig);
		break;
	case 24:
		asdudata = new IEC103Asdu24Data(mConfig);
		break;
	case 25:
		asdudata = new IEC103Asdu24Data(mConfig);
		break;
	case 26:
		asdudata = new IEC103Asdu26Data(mConfig);
		break;
	case 27:
		asdudata = new IEC103Asdu27Data(mConfig);
		break;
	case 28:
		asdudata = new IEC103Asdu28Data(mConfig);
		break;
	case 29:
		asdudata = new IEC103Asdu29Data(mConfig);
		break;
	case 30:
		asdudata = new IEC103Asdu30Data(mConfig);
		break;
	case 31:
		asdudata = new IEC103Asdu24Data(mConfig);
		break;
	case 32:
		asdudata = new IEC103Asdu32Data(mConfig);
		break;
	case 33:
		asdudata = new IEC103Asdu33Data(mConfig);
		break;
	case 34:
		asdudata = new IEC103Asdu34Data(mConfig);
		break;
	case 35:
		asdudata = new IEC103Asdu35Data(mConfig);
		break;
	case 36:
		asdudata = new IEC103Asdu36Data(mConfig);
		break;
	case 37:
		asdudata = new IEC103Asdu37Data(mConfig);
		break;
	case 38:
		asdudata = new IEC103Asdu38Data(mConfig);
		break;
	case 39:
		asdudata = new IEC103Asdu39Data(mConfig);
		break;
	case 40:
		asdudata = new IEC103Asdu40Data(mConfig);
		break;
	case 41:
		asdudata = new IEC103Asdu41Data(mConfig);
		break;
	case 42:
		asdudata = new IEC103Asdu42Data(mConfig);
		break;
	case 43:
		asdudata = new IEC103Asdu43Data(mConfig);
		break;
	case 44:
		asdudata = new IEC103Asdu44Data(mConfig);
		break;
	case 45:
		asdudata = new IEC103Asdu45Data(mConfig);
		break;
	case 46:
		asdudata = new IEC103Asdu46Data(mConfig);
		break;
	case 47:
		asdudata = new IEC103Asdu47Data(mConfig);
		break;
	case 48:
		asdudata = new IEC103Asdu48Data(mConfig);
		break;
	case 50:
		asdudata = new IEC103Asdu50Data(mConfig);
		break;
	case 51:
		asdudata = new IEC103Asdu51Data(mConfig);
		break;
	case 64:
		asdudata = new IEC103Asdu64Data(mConfig);
		break;
	case 65:
		asdudata = new IEC103Asdu65Data(mConfig);
		break;
	case 66:
		asdudata = new IEC103Asdu66Data(mConfig);
		break;
	case 67:
		asdudata = new IEC103Asdu67Data(mConfig);
		break;
	case 88:
		asdudata = new IEC103Asdu88Data(mConfig);
		break;
	case 101:
		asdudata = new IEC103Asdu101Data(mConfig);
		break;
	case 102:
		asdudata = new IEC103Asdu102Data(mConfig);
		break;
	case 103:
		asdudata = new IEC103Asdu103Data(mConfig);
		break;
	case 104:
		asdudata = new IEC103Asdu104Data(mConfig);
		break;
	case 105:
		asdudata = new IEC103Asdu105Data(mConfig);
		break;
	case 106:
		asdudata = new IEC103Asdu106Data(mConfig);
		break;
	case 107:
		asdudata = new IEC103Asdu107Data(mConfig);
		break;
	case 108:
		asdudata = new IEC103Asdu108Data(mConfig);
		break;
	case 220:
		asdudata = new IEC103Asdu220Data(mConfig);
		break;
	case 221:
		asdudata = new IEC103Asdu221Data(mConfig);
		break;
	case 222:
		asdudata = new IEC103Asdu222Data(mConfig);
		break;
	case 223:
		asdudata = new IEC103Asdu223Data(mConfig);
		break;
	case 224:
		asdudata = new IEC103Asdu224Data(mConfig);
		break;
	case 225:
		asdudata = new IEC103Asdu225Data(mConfig);
		break;
	case 226:
		asdudata = new IEC103Asdu226Data(mConfig);
		break;
	case 227:
		asdudata = new IEC103Asdu227Data(mConfig);
		break;
	default:
		break;
	}
	return asdudata;
}





