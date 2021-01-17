#include "functotext.h"

QString prmToText(uchar ch)
{
	QString text = "PRM(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " ";
	if(ch & 0x40)
	{
		text.append("启动站向从动站传输的报文");
	}
	else
	{
		text.append("从动(响应)站向启动站传输的报文");
	}
	return text;
}

QString fcbToText(uchar ch)
{
	QString text = "FCB(bit6):" + QString::number(ch & 0x20, 16).toUpper() + " 帧计数位";
	return text;
}

QString fcvToText(uchar ch)
{
	QString text = "FCV(bit5):" + QString::number(ch & 0x10, 16).toUpper() + " ";
	if(ch & 0x10)
	{
		text.append("表示帧计数位FCB的变化有效");
	}
	else
	{
		text.append("表示帧计数位FCB的变化无效");
	}
	return text;
}

QString acdToText(uchar ch)
{
	QString text = "ACD(bit6):" + QString::number(ch & 0x20, 16).toUpper() + " ";
	if(ch & 0x20)
	{
		text.append("从动站有1级用户数据要求访问");
	}
	else
	{
		text.append("从动站无1级用户数据要求访问");
	}
	return text;
}

QString dfcToText(uchar ch)
{
	QString text = "DFC(bit5):" + QString::number(ch & 0x10, 16).toUpper() + " ";
	if(ch & 0x10)
	{
		text.append("表示从动站接收后续报文将引起数据溢出");
	}
	else
	{
		text.append("表示从动站可以接收后续报文");
	}
	return text;
}

QString cw1ToText(uchar ch)
{
	QString text = "功能码(bit1-4):" + QString::number(ch & 0x0f) + " ";
	switch(ch & 0x0f)
	{
	case 0:
		text.append("帧类型:发送/确认帧  功能描述:复位通信单元  帧计数有效位FCV:0");
		break;
	case 1:
		text.append("帧类型:发送/确认帧  功能描述:用户进程复位  帧计数有效位FCV:0");
		break;
	case 3:
		text.append("帧类型:发送/确认帧  功能描述:传送数据  帧计数有效位FCV:1");
		break;
	case 4:
		text.append("帧类型:发送/无回答帧  功能描述:传送数据  帧计数有效位FCV:0");
		break;
	case 7:
		text.append("帧类型:复位帧计数位  功能描述:传送数据  帧计数有效位FCV:0");
		break;
	case 8:
		text.append("帧类型:要求访问的请求  功能描述:以要求访问位响应  帧计数有效位FCV:0");
		break;
	case 9:
		text.append("帧类型:请求/响应帧  功能描述:召唤链路状态  帧计数有效位FCV:0");
		break;
	case 10:
		text.append("帧类型:请求/响应帧  功能描述:召唤1级数据  帧计数有效位FCV:1");
		break;
	case 11:
		text.append("帧类型:请求/响应帧  功能描述:召唤2级数据  帧计数有效位FCV:1");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString cw2ToText(uchar ch)
{
	QString text = "功能码(bit1-4):" + QString::number(ch & 0x0f) + " ";
	switch(ch & 0x0f)
	{
	case 0:
		text.append("帧类型:确认帧  功能描述:认可，肯定认可");
		break;
	case 1:
		text.append("帧类型:确认帧  功能描述:否定认可，未收到报文，链路忙");
		break;
	case 8:
		text.append("帧类型:响应帧  功能描述:以数据包响应请求帧");
		break;
	case 9:
		text.append("帧类型:响应帧  功能描述:从站没有所召唤的数据");
		break;
	case 11:
		text.append("帧类型:响应帧  功能描述:响应链路状态或要求访问");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString spiToText(uchar ch)
{
	QString text = "单点遥信SPI(bit1):" + QString::number(ch & 0x01) + " ";
	if(ch & 0x01)
	{
		text.append("合位");
	}
	else
	{
		text.append("分位");
	}
	return text;
}

QString dpiToText(uchar ch)
{
	QString text = "双点遥信DPI(bit1-2):" + QString::number(ch & 0x03) + " ";
	switch(ch & 0x03)
	{
	case 1:
		text.append("分位");
		break;
	case 2:
		text.append("合位");
		break;
	default:
		text.append("未知状态");
		break;
	}
	return text;
}

QString dpiteToText(uchar ch)
{
	QString text = "带瞬变与差错的双点遥信DPI(bit1-2):" + QString::number(ch & 0x03) + " ";
	switch(ch & 0x03)
	{
	case 0:
		text.append("瞬变状态");
		break;
	case 1:
		text.append("分位");
		break;
	case 2:
		text.append("合位");
		break;
	case 3:
		text.append("差错状态");
		break;
	default:
		text.append("未知状态");
		break;
	}
	return text;
}

QString scsToText(uchar ch)
{
	QString text = "单点命令(bit1):" + QString::number(ch & 0x01) + " ";
	if(ch & 0x01)
	{
		text.append("合");
	}
	else
	{
		text.append("分");
	}
	return text;
}

QString dcsToText(uchar ch)
{
	QString text = "双点命令(bit1-2):" + QString::number(ch & 0x03) + " ";
	switch(ch & 0x03)
	{
	case 1:
		text.append("分");
		break;
	case 2:
		text.append("合");
		break;
	default:
		text.append("不允许");
		break;
	}
	return text;
}

QString rcsToText_iec101(uchar ch)
{
	QString text = "步调节命令(bit1-2):" + QString::number(ch & 0x03) + " ";
	switch(ch & 0x03)
	{
	case 1:
		text.append("降一步");
		break;
	case 2:
		text.append("升一步");
		break;
	default:
		text.append("不允许");
		break;
	}
	return text;
}

QString rcsToText_iec103(uchar ch)
{
	QString text = "升降命令(bit1-2):" + QString::number(ch & 0x03) + " ";
	switch(ch & 0x03)
	{
	case 1:
		text.append("降一步");
		break;
	case 2:
		text.append("升一步");
		break;
	case 3:
		text.append("急停");
		break;
	default:
		text.append("不允许");
		break;
	}
	return text;
}

QString blToText(uchar ch)
{
	QString text = "BL(bit5):" + QString::number(ch & 0x10, 16).toUpper() + " ";
	if(ch & 0x10)
	{
		text.append("被闭锁");
	}
	else
	{
		text.append("未被闭锁");
	}
	return text;
}

QString sbToText(uchar ch)
{
	QString text = "SB(bit6):" + QString::number(ch & 0x20, 16).toUpper() + " ";
	if(ch & 0x20)
	{
		text.append("被取代");
	}
	else
	{
		text.append("未被取代");
	}
	return text;
}

QString ntToText(uchar ch)
{
	QString text = "NT(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " ";
	if(ch & 0x40)
	{
		text.append("非当前值");
	}
	else
	{
		text.append("当前值");
	}
	return text;
}

QString ivToText(uchar ch)
{
	QString text = "IV(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ";
	if(ch & 0x80)
	{
		text.append("无效");
	}
	else
	{
		text.append("有效");
	}
	return text;
}

QString ovToText(uchar ch)
{
	QString text = "OV(bit1):" + QString::number(ch & 0x01) + " ";
	if(ch & 0x01)
	{
		text.append("溢出");
	}
	else
	{
		text.append("未溢出");
	}
	return text;
}

QString erToText(uchar ch)
{
	QString text = "ER(bit2):" + QString::number(ch & 0x02, 16).toUpper() + " ";
	if(ch & 0x02)
	{
		text.append("被测值无效");
	}
	else
	{
		text.append("被测值有效");
	}
	return text;
}

QString qoiToText(uchar ch)
{
	QString text = "召唤限定词QOI:" + QString::number(ch) + " ";
	switch(ch)
	{
	case 20:
		text.append("站召唤");
		break;
	case 21:
		text.append("第1组召唤");
		break;
	case 22:
		text.append("第2组召唤");
		break;
	case 23:
		text.append("第3组召唤");
		break;
	case 24:
		text.append("第4组召唤");
		break;
	case 25:
		text.append("第5组召唤");
		break;
	case 26:
		text.append("第6组召唤");
		break;
	case 27:
		text.append("第7组召唤");
		break;
	case 28:
		text.append("第8组召唤");
		break;
	case 29:
		text.append("第9组召唤");
		break;
	case 30:
		text.append("第10组召唤");
		break;
	case 31:
		text.append("第11组召唤");
		break;
	case 32:
		text.append("第12组召唤");
		break;
	case 33:
		text.append("第13组召唤");
		break;
	case 34:
		text.append("第14组召唤");
		break;
	case 35:
		text.append("第15组召唤");
		break;
	case 36:
		text.append("第16组召唤");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString coiToText(uchar ch)
{
	QString text = "初始化原因(bit1-7):" + QString::number(ch & 0x7f) + " ";
	switch(ch & 0x7f)
	{
	case 0:
		text.append("当地电源合上");
		break;
	case 1:
		text.append("当地手动复位");
		break;
	case 2:
		text.append("远方复位");
		break;
	default:
		text.append("保留");
		break;
	}
	text.append("   BS(bit8):") + QString::number(ch & 0x80, 16).toUpper() + " ";
	if(ch & 0x80)
	{
		text.append("改变当地参数后的初始化");
	}
	else
	{
		text.append("未改变当地参数后的初始化");
	}
	return text;
}

QString rqtToText(uchar ch)
{
	QString text = "请求RQT(bit1-6):"  + QString::number(ch & 0x3f) + " ";
	switch(ch & 0x3f)
	{
	case 0:
		text.append("无电能脉冲计数量被请求");
		break;
	case 1:
		text.append("请求计数量第1组");
		break;
	case 2:
		text.append("请求计数量第1组");
		break;
	case 3:
		text.append("请求计数量第3组");
		break;
	case 4:
		text.append("请求计数量第4组");
		break;
	case 5:
		text.append("电能脉冲计数量的总请求");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString frzToText(uchar ch)
{
	QString text = "冻结FRZ(bit7-8):"  + QString::number(ch & 0xc0, 16).toUpper() + " ";
	switch(ch >> 6)
	{
	case 0:
		text.append("无冻结或复位");
		break;
	case 1:
		text.append("电能脉冲计数量冻结不带复位（被冻结的值为累计量）");
		break;
	case 2:
		text.append("电能脉冲计数量冻结带复位（被冻结的值为增量信息）");
		break;
	case 3:
		text.append("电能脉冲计数量复位");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString suToText(uchar ch)
{
	QString text = "SU(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ";
	if(ch & 0x80)
	{
		text.append("夏季时间");
	}
	else
	{
		text.append("标准时间");
	}
	return text;
}

QString quToText_iec101(uchar ch)
{
	QString text = "QU(bit3-7):" + QString::number(ch & 0x7c, 16).toUpper() + " ";
	switch((ch & 0x7c) >> 2)
	{
	case 0:
		text.append("无另外的定义");
		break;
	case 1:
		text.append("短脉冲持续时间(断路器)，持续时间由被控站内的系统参数所确定");
		break;
	case 2:
		text.append("长脉冲持续时间，持续时间由被控站内的系统参数所确定");
		break;
	case 3:
		text.append("持续输出");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString quToText_iec103(uchar ch)
{
	QString text = "QU(bit3-6):" + QString::number(ch & 0x3c, 16).toUpper() + " ";
	switch((ch & 0x3c) >> 2)
	{
	case 0:
		text.append("被寻址的控制功能的属性(如脉冲持续时间等),这些属性在被控站事先定义而不由控制中心来选择");
		break;
	case 1:
		text.append("短脉冲持续时间(断路器)，持续时间由远方终端系统参数所定义");
		break;
	case 2:
		text.append("长脉冲持续时间，持续时间由远方终端系统参数所定义");
		break;
	case 3:
		text.append("持续输出");
		break;
	case 4:
		text.append("不闭锁重合闸的跳闸命令,用于检查小电流接地系统的接地故障,跳闸后,母线零序电压为零,该断路器就不进行重合闸;"
					"如果母线零序电压不为零,经过一个时间延时,该断路器就进行重合闸");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString seToText(uchar ch)
{
	QString text = "S/E(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ";
	if(ch & 0x80)
	{
		text.append("命令类型:选择");
	}
	else
	{
		text.append("命令类型:执行");
	}
	return text;
}

QString caToText(uchar ch)
{
	QString text = "CA(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " ";
	if(ch & 0x40)
	{
		text.append("上次读数后计数器被调整");
	}
	else
	{
		text.append("上次读数后计数器未被调整");
	}
	return text;
}

QString cyToText(uchar ch)
{
	QString text = "CY(bit6):" + QString::number(ch & 0x20, 16).toUpper() + " ";
	if(ch & 0x20)
	{
		text.append("在相应的累加周期内计数器溢出");
	}
	else
	{
		text.append("在相应的累加周期内计数器未溢出");
	}
	return text;
}

QString vtiToText_iec101(uchar ch)
{
	QString text = "步位置(bit1-7):"  + QString::number(ch & 0x7f) ;

	text.append("   瞬变状态BS1(bit8):") + QString::number(ch & 0x80, 16).toUpper() + " ";
	if(ch & 0x80)
	{
		text.append("设备在瞬变状态");
	}
	else
	{
		text.append("设备未在瞬变状态");
	}
	return text;
}
QString vtiToText_iec103(uchar ch)
{
	uchar tmp = ch << 1;
	char datachar = (*(char *)&tmp) >> 1;
	QString text = "带瞬变状态指示的值VTI(bit1-7):"  + QString::number(datachar) ;

	text.append("   瞬变状态BS1(bit8):") + QString::number(ch & 0x80, 16).toUpper() + " ";
	if(ch & 0x80)
	{
		text.append("设备在瞬变状态");
	}
	else
	{
		text.append("设备未在瞬变状态");
	}
	return text;
}

QString qosToText(uchar ch)
{
	QString text = "设定命令限定词QOS";
	text.append("  QL(bit1-7):" + QString::number(ch & 0x7f) + "   " + seToText(ch));
	return text;
}

QString timeToText(const char *time, int timelen)
{
	uchar *mtime = (uchar *)time;
	return timeToText(mtime, timelen);
}

QString timeToText(uchar *time, int timelen)
{
	QString text;

	if(timelen < 2)
	{
		return text;
	}

	QDateTime datetime = charToDateTime(time, timelen, BINARYTIME2A);

	uint datauint = charTouint(time, 2);
	text.append(CharToHexStr(time, 2) + "\t" + QString::number(datauint) + "   秒:" + QString::number(datetime.time().second()) + "   毫秒:" + QString::number(datetime.time().msec()) + " \r\n");
	if(timelen == 2)
	{
		return text;
	}

	text.append(CharToHexStr(time[2]) + "\t分(bit1-6):" + QString::number(datetime.time().minute()) + "   " + ivToText(time[2]) + "\r\n");
	if(timelen == 3)
	{
		return text;
	}

	text.append(CharToHexStr(time[3]) + "\t时(bit1-5):" + QString::number(datetime.time().hour()) + "   " + suToText(time[3]) + "\r\n");
	if(timelen == 4)
	{
		return text;
	}

	text.append(CharToHexStr(time[4]) + "\t日(bit1-5):" + QString::number(datetime.date().day()) + "   周(bit6-8):" + QString::number(time[4] >> 5) + " (7表示星期天,0表示未用)\r\n");
	if(timelen == 5)
	{
		return text;
	}

	text.append(CharToHexStr(time[5]) + "\t月(bit1-4):" + QString::number(datetime.date().month()) + "\r\n");
	if(timelen == 6)
	{
		return text;
	}

	text.append(CharToHexStr(time[6]) + "\t年(bit1-7):" + QString::number(datetime.date().year()) + "\r\n");
	return text;
}
QString ndeToText(uchar ch)
{
	QString text;
	text.append("NO(bit1-6):" + QString::number(ch & 0x3f) + " 描述元素数目\r\n\t");
	text.append("COUNT(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " 具有相同的通用分类标识序号(GIN)和相同返回标识符(RII)的应用服务数据单元通用分类标识的一位计数器位\r\n\t");
	text.append("CONT(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ");
	if(ch & 0x80)
	{
		text.append("后面跟随具有相同的返回标识符(RII)和相同的通用分类标识序号(GIN)的应用服务数据单元");
	}
	else
	{
		text.append("后面未跟随具有相同的返回标识符(RII)和相同的通用分类标识序号(GIN)的应用服务数据单元");
	}
	return text;
}

QString ngdToText(uchar ch)
{
	QString text;
	text.append("NO(bit1-6):" + QString::number(ch & 0x3f) + " 通用分类数据集数目\r\n\t");
	text.append("COUNT(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " 具有相同返回信息标识符(RII)的应用服务数据单元的一位计数器位\r\n\t");
	text.append("CONT(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ");
	if(ch & 0x80)
	{
		text.append("后面跟着具有相同返回信息标识符(RII)的应用服务数据单元");
	}
	else
	{
		text.append("后面未跟着具有相同返回信息标识符(RII)的应用服务数据单元");
	}
	return text;
}

QString nogToText(uchar ch)
{
	QString text;
	text.append("NOG:" + QString::number(ch) + " 通用分类标识数目");
	return text;
}
QString kodToText(uchar ch)
{
	QString text = "KOD:" + QString::number(ch) + " ";
	switch(ch)
	{
	case 0:
		text.append("无所指定的描述类别");
		break;
	case 1:
		text.append("实际值");
		break;
	case 2:
		text.append("缺省值");
		break;
	case 3:
		text.append("量程(最小值最大值步长)");
		break;
	case 5:
		text.append("精度(n m)");
		break;
	case 6:
		text.append("因子");
		break;
	case 7:
		text.append("%参比");
		break;
	case 8:
		text.append("列表");
		break;
	case 9:
		text.append("量纲");
		break;
	case 10:
		text.append("描述");
		break;
	case 12:
		text.append("口令条目");
		break;
	case 13:
		text.append("只读");
		break;
	case 14:
		text.append("只写");
		break;
	case 19:
		text.append("相应的功能类型和信息序号");
		break;
	case 20:
		text.append("相应的事件");
		break;
	case 21:
		text.append("列表的文本阵列");
		break;
	case 22:
		text.append("列表的值阵列");
		break;
	case 23:
		text.append("相关联的条目");
		break;
	case 103:
		text.append("属性结构(保信规约专用)");
		break;
	default:
		text.append("备用");
		break;
	}
	return text;
}

QString gdd1ToText(uchar ch)
{
	QString text = "GDD1:" + QString::number(ch) + " ";
	switch(ch)
	{
	case 0:
		text.append("无数据");
		break;
	case 1:
		text.append("OS8(ASCII8位码)");
		break;
	case 2:
		text.append("成组8位串");
		break;
	case 3:
		text.append("无符号整数");
		break;
	case 4:
		text.append("整数");
		break;
	case 5:
		text.append("无符号浮点数");
		break;
	case 6:
		text.append("浮点数");
		break;
	case 7:
		text.append("IEEE标准754短实数");
		break;
	case 8:
		text.append("IEEE标准754实数");
		break;
	case 9:
		text.append("双点信息");
		break;
	case 10:
		text.append("单点信息");
		break;
	case 11:
		text.append("带瞬变和差错的双点信息");
		break;
	case 12:
		text.append("带品质描述词的被测值");
		break;
	case 14:
		text.append("二进制时间");
		break;
	case 15:
		text.append("通用分类标识序号");
		break;
	case 16:
		text.append("相对时间");
		break;
	case 17:
		text.append("功能类型和信息序号");
		break;
	case 18:
		text.append("带时标的报文");
		break;
	case 19:
		text.append("带相对时间的时标报文");
		break;
	case 20:
		text.append("带相对时间的时标的被测值");
		break;
	case 21:
		text.append("外部文本序号");
		break;
	case 22:
		text.append("通用分类回答码");
		break;
	case 23:
		text.append("数据结构");
		break;
	case 24:
		text.append("索引");
		break;
	case 201:
		text.append("遥脉数据");
		break;
	case 205:
		text.append("故障测量数据");
		break;
	default:
		text.append("备用");
		break;
	}
	return text;
}

QString gdd3ToText(uchar ch)
{
	QString text;
	text.append("GDD3:NUMBER(bit1-7):" + QString::number(ch & 0x7f) + " 信息数目   ");
	text.append("CONT(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ");
	if(ch & 0x80)
	{
		text.append("后面跟随的数据元素具有相同的返回信息标识符(RII)");
	}
	else
	{
		text.append("后面未跟随数据元素");
	}
	return text;
}

QString grcToText(uchar ch)
{
	QString text = "GRC:" + QString::number(ch) + "通用分类回答码:" ;
	switch(ch)
	{
	case 0:
		text.append("认可");
		break;
	case 1:
		text.append("无效的通用分类标识序号（GIN）");
		break;
	case 2:
		text.append("不存在所请求的数据");
		break;
	case 3:
		text.append("数据不能用，过后再来一次");
		break;
	case 4:
		text.append("改变设定时确认出错");
		break;
	case 5:
		text.append("改变设定时超出量程");
		break;
	case 6:
		text.append("条目的范围太大");
		break;
	case 7:
		text.append("太多的命令");
		break;
	case 8:
		text.append("条目是只读");
		break;
	case 9:
		text.append("设定受口令保护");
		break;
	case 10:
		text.append("当地设定在进行中");
		break;
	case 11:
		text.append("带有下面所描述的差错");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString sofToText(uchar ch)
{
	QString text;
	text.append("故障状态SOF:");
	text.append("\r\n\tTP(bit1):" + QString::number(ch & 0x01, 16).toUpper() + " ");
	if(ch & 0x01)
	{
		text.append("被记录的故障跳闸");
	}
	else
	{
		text.append("被记录的故障未跳闸");
	}

	text.append("\r\n\tTM(bit2):" + QString::number(ch & 0x02, 16).toUpper() + " ");
	if(ch & 0x02)
	{
		text.append("扰动数据正在传输");
	}
	else
	{
		text.append("扰动数据等待传输");
	}

	text.append("\r\n\tTEST(bit3):" + QString::number(ch & 0x04, 16).toUpper() + " ");
	if(ch & 0x04)
	{
		text.append("在测试模式下被记录的扰动数据");
	}
	else
	{
		text.append("在正常操作时被记录的扰动数据");
	}

	text.append("\r\n\tOTEV(bit4):" + QString::number(ch & 0x08, 16).toUpper() + " ");
	if(ch & 0x08)
	{
		text.append("由其他事件触发被记录的扰动数据");
	}
	else
	{
		text.append("由启动/检出故障触发被记录的扰动数据");
	}
	return text;
}

QString sofToText_iec101(uchar ch)
{
	QString text = "文件状态SOF:";
	text.append("\r\n\tSTATUS(bit1-5):" + QString::number(ch & 0x1f, 16).toUpper() + " ");
	switch(ch & 0x1f)
	{
	case 0:
		text.append("缺省");
		break;
	default:
		text.append("预留");
		break;
	}

	text.append("\r\n\tLFD(bit6):" + QString::number(ch & 0x20, 16).toUpper() + " ");
	if(ch & 0x20)
	{
		text.append("最后目录文件");
	}
	else
	{
		text.append("后面还有目录文件");
	}
	text.append("\r\n\tFOR(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " ");
	if(ch & 0x40)
	{
		text.append("定义子目录名");
	}
	else
	{
		text.append("定义文件名");
	}
	text.append("\r\n\tFA(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ");
	if(ch & 0x80)
	{
		text.append("文件传输已被激活");
	}
	else
	{
		text.append("文件等待传输");
	}
	return text;
}

QString sofToText_iec103(uchar ch)
{
	QString text = "文件状态SOF:";
	text.append("\r\n\tSTATUS(bit1-5):" + QString::number(ch & 0x1f, 16).toUpper() + " ");
	switch(ch & 0x1f)
	{
	case 0:
		text.append("未用");
		break;
	default:
		text.append("预留");
		break;
	}

	text.append("\r\n\tRES1(bit6):" + QString::number(ch & 0x20, 16).toUpper() + " 预留");
	text.append("\r\n\tFOR(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " 预留");
	text.append("\r\n\tFA(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ");
	if(ch & 0x80)
	{
		text.append("文件传输已被激活");
	}
	else
	{
		text.append("文件等待传输");
	}
	return text;
}

QString tooToText(uchar ch)
{
	QString text;
	text.append("命令类型TOO:" + QString::number(ch) + "   ");
	switch(ch)
	{
	case 1:
		text.append("故障的选择");
		break;
	case 2:
		text.append("请求扰动数据");
		break;
	case 3:
		text.append("中止扰动数据");
		break;
	case 8:
		text.append("通道的请求");
		break;
	case 9:
		text.append("通道的中止");
		break;
	case 16:
		text.append("请求带标志的状态变位");
		break;
	case 17:
		text.append("中止带标志的状态变位");
		break;
	case 24:
		text.append("请求被记录扰动表");
		break;
	case 32:
		text.append("不带中止的扰动数据传输的结束");
		break;
	case 33:
		text.append("由控制系统所中止的扰动数据传输的结束");
		break;
	case 34:
		text.append("由继电保护设备(或间隔单元)所中止的扰动数据传输的结束");
		break;
	case 35:
		text.append("不带中止的通道传输的结束");
		break;
	case 36:
		text.append("由控制系统所中止的通道传输的结束");
		break;
	case 37:
		text.append("由继电保护设备(或间隔单元)所中止的通道传输的结束");
		break;
	case 38:
		text.append("不带中止的带标志的状态变位的传输的结束");
		break;
	case 39:
		text.append("由控制系统所中止的带标志的状态变位的传输的结束");
		break;
	case 40:
		text.append("由继电保护设备(或间隔单元)所中止的带标志的状态变位传输的结束");
		break;
	case 64:
		text.append("成功的扰动数据传输(肯定)");
		break;
	case 65:
		text.append("不成功的扰动数据传输(否定)");
		break;
	case 66:
		text.append("成功的通道传输(肯定)");
		break;
	case 67:
		text.append("不成功的通道传输(否定)");
		break;
	case 68:
		text.append("成功的带标志的状态变位传输(肯定)");
		break;
	case 69:
		text.append("不成功的带标志的状态变位传输(否定)");
		break;
	default:
		text.append("备用");
		break;
	}
	return text;
}

QString tovToText(uchar ch)
{
	QString text = "扰动值的类型TOV:" + QString::number(ch) + "   ";
	if(ch == 1)
	{
		text.append("瞬时值");
	}
	else
	{
		text.append("未定义");
	}
	return text;
}

QString accToText(uchar ch)
{
	QString text = "实际通道序号ACC:" + QString::number(ch) + "   ";
	switch(ch)
	{
	case 0:
		text.append("全局");
		break;
	case 1:
		text.append("Ia");
		break;
	case 2:
		text.append("Ib");
		break;
	case 3:
		text.append("Ic");
		break;
	case 4:
		text.append("I0");
		break;
	case 5:
		text.append("Ua");
		break;
	case 6:
		text.append("Ub");
		break;
	case 7:
		text.append("Uc");
		break;
	case 8:
		text.append("U0");
		break;
	default:
		text.append("备用");
		break;
	}
	return text;
}

QString scqToText_iec101(uchar ch)
{
	QString text = "选择召唤限定词SCQ:\r\n\tbit(1-4): " + QString::number(ch & 0x0f) + "  ";
	switch(ch & 0x0f)
	{
	case 0:
		text.append("未用");
		break;
	case 1:
		text.append("选择文件");
		break;
	case 2:
		text.append("请求文件");
		break;
	case 3:
		text.append("停止激活文件");
		break;
	case 4:
		text.append("删除文件");
		break;
	case 5:
		text.append("选择节");
		break;
	case 6:
		text.append("请求节");
		break;
	case 7:
		text.append("停止激活节");
		break;
	default:
		text.append("保留");
		break;
	}
	text.append("\r\n\tbit(5-8): " + QString::number((ch >> 4) & 0x0f) + "  ");
	switch((ch >> 4) & 0x0f)
	{
	case 0:
		text.append("未用");
		break;
	case 1:
		text.append("无被请求的存储空间");
		break;
	case 2:
		text.append("校验和错");
		break;
	case 3:
		text.append("非所期望的通信服务");
		break;
	case 4:
		text.append("非所期望的文件名称");
		break;
	case 5:
		text.append("非所期望的节名称");
		break;
	default:
		text.append("保留");
		break;
	}

	return text;
}
QString scqToText_iec103(uchar ch)
{
	QString text = "选择召唤限定词SCQ:\r\n\tbit(1-4): " + QString::number(ch & 0x0f) + "  ";
	switch(ch & 0x0f)
	{
	case 0:
		text.append("未用");
		break;
	case 1:
		text.append("选择文件");
		break;
	case 2:
		text.append("召唤文件");
		break;
	case 3:
		text.append("停止激活文件");
		break;
	case 4:
		text.append("删除文件");
		break;
	case 5:
		text.append("召唤节");
		break;
	case 6:
		text.append("停止激活节");
		break;
	case 7:
		text.append("召唤目录");
		break;
	default:
		text.append("保留");
		break;
	}
	text.append("\r\n\tbit(5-8): " + QString::number((ch >> 4) & 0x0f) + "  ");
	switch((ch >> 4) & 0x0f)
	{
	case 0:
		text.append("未用");
		break;
	case 1:
		text.append("无被请求的存储空间");
		break;
	case 2:
		text.append("非所期望的通信服务");
		break;
	case 3:
		text.append("非所期望的文件名称");
		break;
	case 4:
		text.append("非所期望的节名称");
		break;
	default:
		text.append("保留");
		break;
	}

	return text;
}


QString frqToText(uchar ch)
{
	QString text = "文件准备就绪限定词FRQ:";
	text.append("\r\n\tbit(1-7):" + QString::number(ch & 0x7f, 16).toUpper() + " 预留");
	text.append("\r\n\tbit8: " + QString::number(ch & 0x80, 16) + "  ");
	if(ch & 0x80)
	{
		text.append("选择、请求、停止激活或删除的否定确认");
	}
	else
	{
		text.append("选择、请求、停止激活或删除的肯定确认");
	}
	return text;
}

QString srqToText(uchar ch)
{
	QString text = "节准备就绪限定词SRQ:";
	text.append("\r\n\tbit(1-7):" + QString::number(ch & 0x7f, 16).toUpper() + " 预留");
	text.append("\r\n\tbit8: " + QString::number(ch & 0x80, 16) + "  ");
	if(ch & 0x80)
	{
		text.append("节未准备就绪");
	}
	else
	{
		text.append("节准备就绪");
	}
	return text;
}

QString lsqToText_iec101(uchar ch)
{
	QString text = "最后的节和段限定词LSQ: " + QString::number(ch) + "  ";
	switch(ch)
	{
	case 0:
		text.append("未用");
		break;
	case 1:
		text.append("不带停止激活的文件传输");
		break;
	case 2:
		text.append("带停止激活的文件传输");
		break;
	case 3:
		text.append("不带停止激活的节传输");
		break;
	case 4:
		text.append("带停止激活的节传输");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString lsqToText_iec103(uchar ch)
{
	QString text = "最后的节和段限定词LSQ: " + QString::number(ch) + "  ";
	switch(ch)
	{
	case 0:
		text.append("未用");
		break;
	case 1:
		text.append("不带停止激活的节传输");
		break;
	case 2:
		text.append("带停止激活的节传输");
		break;
	case 3:
		text.append("不带停止激活的段传输");
		break;
	case 4:
		text.append("带停止激活的段传输");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString afqToText_iec101(uchar ch)
{
	QString text = "文件认可或节认可限定词AFQ:\r\n\tbit(1-4): " + QString::number(ch & 0x0f) + "  ";
	switch(ch & 0x0f)
	{
	case 0:
		text.append("缺省");
		break;
	case 1:
		text.append("文件传输的肯定认可");
		break;
	case 2:
		text.append("文件传输的否定认可");
		break;
	case 3:
		text.append("节传输的肯定认可");
		break;
	case 4:
		text.append("节传输的否定认可");
		break;
	default:
		text.append("保留");
		break;
	}
	text.append("\r\n\tbit(5-8): " + QString::number((ch >> 4) & 0x0f) + "  ");
	switch((ch >> 4) & 0x0f)
	{
	case 0:
		text.append("缺省");
		break;
	case 1:
		text.append("无被请求的存储空间");
		break;
	case 2:
		text.append("校验和错");
		break;
	case 3:
		text.append("非所期望的通信服务");
		break;
	case 4:
		text.append("非所期望的文件名称");
		break;
	case 5:
		text.append("非所期望的节名称");
		break;
	default:
		text.append("保留");
		break;
	}

	return text;
}

QString afqToText_iec103(uchar ch)
{
	QString text = "文件认可或节认可限定词AFQ:\r\n\tbit(1-4): " + QString::number(ch & 0x0f) + "  ";
	switch(ch & 0x0f)
	{
	case 0:
		text.append("未用");
		break;
	case 1:
		text.append("文件传输的肯定认可");
		break;
	case 2:
		text.append("文件传输的否定认可");
		break;
	case 3:
		text.append("节传输的肯定认可");
		break;
	case 4:
		text.append("节传输的否定认可");
		break;
	default:
		text.append("保留");
		break;
	}
	text.append("\r\n\tbit(5-8): " + QString::number((ch >> 4) & 0x0f) + "  ");
	switch((ch >> 4) & 0x0f)
	{
	case 0:
		text.append("未用");
		break;
	case 1:
		text.append("无被请求的存储空间");
		break;
	case 2:
		text.append("非所期望的通信服务");
		break;
	case 3:
		text.append("非所期望的文件名称");
		break;
	case 4:
		text.append("非所期望的节名称");
		break;
	default:
		text.append("保留");
		break;
	}

	return text;
}


QString esToText(uchar ch)
{
	QString text = "事件状态ES(bit1-2):" + QString::number(ch & 0x03) + " ";
	switch(ch & 0x03)
	{
	case 0:
		text.append("不确定或中间状态");
		break;
	case 1:
		text.append("分");
		break;
	case 2:
		text.append("合");
		break;
	case 3:
		text.append("不确定");
		break;
	default:
		text.append("不确定");
		break;
	}
	return text;
}

QString eiToText(uchar ch)
{
	QString text = "EI(bit4):" + QString::number(ch & 0x08, 16).toUpper() + " ";
	if(ch & 0x08)
	{
		text.append("动作时间无效");
	}
	else
	{
		text.append("动作时间有效");
	}
	return text;
}

QString gsToText(uchar ch)
{
	QString text = "GS(bit1):" + QString::number(ch & 0x01, 16).toUpper() + " ";
	if(ch & 0x01)
	{
		text.append("总启动");
	}
	else
	{
		text.append("无总启动");
	}
	return text;
}

QString sl1ToText(uchar ch)
{
	QString text = "SL1(bit2):" + QString::number(ch & 0x02, 16).toUpper() + " ";
	if(ch & 0x02)
	{
		text.append("A相保护启动");
	}
	else
	{
		text.append("A相保护未启动");
	}
	return text;
}

QString sl2ToText(uchar ch)
{
	QString text = "SL2(bit3):" + QString::number(ch & 0x04, 16).toUpper() + " ";
	if(ch & 0x04)
	{
		text.append("B相保护启动");
	}
	else
	{
		text.append("B相保护未启动");
	}
	return text;
}

QString sl3ToText(uchar ch)
{
	QString text = "SL3(bit4):" + QString::number(ch & 0x08, 16).toUpper() + " ";
	if(ch & 0x08)
	{
		text.append("C相保护启动");
	}
	else
	{
		text.append("C相保护未启动");
	}
	return text;
}

QString sieToText(uchar ch)
{
	QString text = "SIE(bit5):" + QString::number(ch & 0x10, 16).toUpper() + " ";
	if(ch & 0x10)
	{
		text.append("接地电流保护启动");
	}
	else
	{
		text.append("接地电流保护未启动");
	}
	return text;
}

QString srdToText(uchar ch)
{
	QString text = "SRD(bit6):" + QString::number(ch & 0x20, 16).toUpper() + " ";
	if(ch & 0x20)
	{
		text.append("反向保护启动");
	}
	else
	{
		text.append("反向保护未启动");
	}
	return text;
}

QString cl1ToText(uchar ch)
{
	QString text = "CL1(bit2):" + QString::number(ch & 0x02, 16).toUpper() + " ";
	if(ch & 0x02)
	{
		text.append("命令输出至A相输出电路");
	}
	else
	{
		text.append("无命令输出至A相输出电路");
	}
	return text;
}

QString cl2ToText(uchar ch)
{
	QString text = "CL2(bit3):" + QString::number(ch & 0x04, 16).toUpper() + " ";
	if(ch & 0x04)
	{
		text.append("命令输出至B相输出电路");
	}
	else
	{
		text.append("无命令输出至B相输出电路");
	}
	return text;
}

QString cl3ToText(uchar ch)
{
	QString text = "CL3(bit4):" + QString::number(ch & 0x08, 16).toUpper() + " ";
	if(ch & 0x08)
	{
		text.append("命令输出至C相输出电路");
	}
	else
	{
		text.append("无命令输出至C相输出电路");
	}
	return text;
}

QString qrpToText(uchar ch)
{
	QString text = "复位进程命令限定词QRP: " + QString::number(ch) + "  ";
	switch(ch)
	{
	case 0:
		text.append("未用");
		break;
	case 1:
		text.append("进程的总复位");
		break;
	case 2:
		text.append("复位事件缓冲区等待处理的带时标的信息");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString qpmToText(uchar ch)
{
	QString text = "测量值参数限定词QPM:\r\n\t参数类别KPA(bit1-6): " + QString::number(ch & 0x3f) + "  ";
	switch(ch & 0x3f)
	{
	case 0:
		text.append("未用");
		break;
	case 1:
		text.append("门限值");
		break;
	case 2:
		text.append("平滑系数(滤波时间常数)");
		break;
	case 3:
		text.append("传送测量值的下限");
		break;
	case 4:
		text.append("传送测量值的上限");
		break;
	default:
		text.append("保留");
		break;
	}
	text.append("\r\n\tLPC(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " ");
	if(ch & 0x40)
	{
		text.append("当地参数改变");
	}
	else
	{
		text.append("当地参数未改变");
	}
	text.append("\r\n\tPOP(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ");
	if(ch & 0x80)
	{
		text.append("参数未运行");
	}
	else
	{
		text.append("参数在运行");
	}

	return text;
}

QString qpaToText(uchar ch)
{
	QString text = "参数激活限定词QPA: " + QString::number(ch) + "  ";
	switch(ch)
	{
	case 0:
		text.append("未用");
		break;
	case 1:
		text.append("激活/停止激活这之前装载的参数(信息对象地址=0)");
		break;
	case 2:
		text.append("激活/停止激活所寻址信息对象的参数");
		break;
	case 3:
		text.append("激活/停止激活所寻址的持续循环或周期传输的信息对象");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}


QString colToText(uchar ch)
{
	QString text = "兼容级别COL: " + QString::number(ch) + "  ";
	switch(ch)
	{
	case 2:
		text.append("基于本配套标准所定义的但未采用通用分类服务的继电保护设备(或间隔单元)");
		break;
	case 3:
		text.append("采用通用分类服务");
		break;
	default:
		text.append("未定义");
		break;
	}
	return text;
}

QString hrToText(const char *ch, int len)
{
	uchar *mch = (uchar *)ch;
	return hrToText(mch, len);
}

QString hrToText(uchar *ch, int len)
{
	QString text ;
	uint data = charTouint(ch, len);
	if(len == 3)
	{
		text.append(CharToHexStr(ch) + "带品质描述的被测谐波值MEA:\r\n\t顺序SQ(bit1-4): " + QString::number(data & 0x0f) + "  此谐波值为对应帧内测量值的顺序号,0对应第一个量");
		text.append("\r\n\t谐波次数HRTM(bit5-8): " + QString::number((data >> 4) & 0x0f) + "\r\n");
		short datashort = charToshortwithQ(ch + 1) >> 2;
		text.append(CharToHexStr(ch + 1, 2) + "\t带品质描述词的被测值(bit4-16):" + QString::number(datashort) + "   " + ovToText(*(ch + 1)) + "   " + erToText(*(ch + 1)));
	}
	else if(len == 4)
	{
		text.append(CharToHexStr(ch) + "带品质描述的被测谐波值向量MEA:\r\n\t顺序SQ(bit1-3): " + QString::number(data & 0x07) + "  此谐波值为对应帧内测量值的顺序号,0对应第一个量");
		text.append("\r\n\t谐波次数HRTM(bit4-7): " + QString::number((data >> 3) & 0x0f));
		text.append("\r\n\tER(bit8):" + QString::number(*ch & 0x80, 16).toUpper() + " ");
		if(*ch & 0x80)
		{
			text.append("谐波值无效");
		}
		else
		{
			text.append("谐波值有效");
		}
		text.append("\r\n");
		ushort dataushort = (data >> 3) & 0xffff;
		short datashort = (*(short *)&dataushort) >> 5;
		text.append(CharToHexStr(ch + 1, 3) + "\t谐波实数值(bit9-19):" + QString::number(datashort));
		text.append("\r\n\tOVr(bit20):" + QString::number(*(ch + 2) & 0x08, 16).toUpper() + " ");
		if(*(ch + 2) & 0x08)
		{
			text.append("实数部分溢出");
		}
		else
		{
			text.append("实数部分无溢出");
		}
		dataushort = (data >> 15) & 0xffff;
		datashort = (*(short *)&dataushort) >> 5;
		text.append("\r\n\t谐波虚数值(bit21-31):" + QString::number(datashort));
		text.append("\r\n\tOVi(bit32):" + QString::number(*(ch + 3) & 0x80, 16).toUpper() + " ");
		if(*(ch + 3) & 0x80)
		{
			text.append("虚数部分溢出");
		}
		else
		{
			text.append("虚数部分无溢出");
		}
	}

	return text;
}


QString actToText(uchar ch)
{
	QString text = "ACT(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " ";
	if(ch & 0x40)
	{
		text.append("撤销");
	}
	else
	{
		text.append("命令有效");
	}
	return text;
}

QString ccsToText(uchar ch)
{
	QString text = "控制命令状态CCS: " + QString::number(ch & 0x07) + "  ";
	switch(ch & 0x07)
	{
	case 0:
		text.append("不允许");
		break;
	case 1:
		text.append("选择自同期设备的同期工作方式");
		break;
	case 2:
		text.append("选择自同期设备的不检同期工作方式");
		break;
	case 3:
		text.append("选择自同期设备的检无压工作方式");
		break;
	case 4:
		text.append("选择自同期设备的合环(母线有电压)工作方式");
		break;
	default:
		text.append("备用");
		break;
	}
	return text;
}

QString myTime1ToText(const char *time, int timelen)
{
	uchar *mtime = (uchar *)time;
	return myTime1ToText(mtime, timelen);
}

QString myTime1ToText(uchar *time, int timelen)
{
	QString text;

	if(timelen != 4)
	{
		return text;
	}

	QDateTime datetime = charToDateTime(time, timelen, MYTIME1);

	text.append(CharToHexStr(time[0]) + "\t秒:" + QString::number(datetime.time().second()) + "\r\n");
	text.append(CharToHexStr(time[1]) + "\t分:" + QString::number(datetime.time().minute()) + "\r\n");
	text.append(CharToHexStr(time[2]) + "\t时:" + QString::number(datetime.time().hour()) + "\r\n");
	text.append(CharToHexStr(time[3]) + "\t日:" + QString::number(datetime.date().day()) + "\r\n");

	return text;
}

QString myTime2ToText(const char *time, int timelen)
{
	uchar *mtime = (uchar *)time;
	return myTime2ToText(mtime, timelen);
}

QString myTime2ToText(uchar *time, int timelen)
{
	QString text;

	if(timelen != 6)
	{
		return text;
	}

	QDateTime datetime = charToDateTime(time, timelen, MYTIME2);

	text.append(CharToHexStr(time[0]) + "\t分:" + QString::number(datetime.time().minute()) + "\r\n");
	text.append(CharToHexStr(time[1]) + "\t时:" + QString::number(datetime.time().hour()) + "\r\n");
	text.append(CharToHexStr(time[2]) + "\t日:" + QString::number(datetime.date().day()) + "\r\n");
	text.append(CharToHexStr(time[3]) + "\t月:" + QString::number(datetime.date().month()) + "\r\n");
	text.append(CharToHexStr(&time[4], 2) + "\t年:" + QString::number(datetime.date().year()) + "\r\n");
	return text;
}
