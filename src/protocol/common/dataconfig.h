#ifndef DATACONFIG_H
#define DATACONFIG_H

#include "globaldefine.h"

struct ModbusDataGroup
{
	uchar dataLen;		//应答报文数据字节数
	QString type;		//数据类型
	QString analysis;	//解析码
	QString sort;		//顺序
};

struct MyConfig
{
	QString lengthType;			//长度域类型
	int addrLen;				//地址域字节数
	int cotlen ;				//cot长度
	int comaddrlen ;			//公共地址长度
	int infaddrlen ;			//信息体地址长度
	QList<ModbusDataGroup *> groups;	//界面提供的解析方式
};

class IECDataConfig
{
public:
	IECDataConfig();
	~IECDataConfig();
	QByteArray data;		//总报文
	QByteArray userdata;	//自定义asdu报文
	int masterState;		//主站状态
	int slaveState;			//子站状态
	bool isMaster;			//是否为主站
	/***数据*************************/
	bool isfirst;			//是否是第一个信息体
	uchar controltype;		//帧类型 I、U、S 帧
	uchar asdutype;			//asdu类型
	uchar cot;              //传送原因
	uint comaddr;			//公共地址
	uchar vsq;              //信息元素个数
	uint infaddr;			//信息体地址
	QByteArray infdata;		//信息体数据
	/***IEC103参数*************************/
	uchar fun;
	uchar inf;
	uchar rii;
	uchar ngd;				//通用分类数据集数目，包括GIN、KOD、GDD、GID
	uchar nog;				//通用分类标识数目，包括GIN、KOD
	uchar gin[20][2];
	uchar kod[20];
	uchar gdd[20][3];
	uchar gid[255];
	/***IEC104 167号报文************************/
	IECDataConfig *iec103config;
	ushort devaddr;
};


#endif // DATACONFIG_H
