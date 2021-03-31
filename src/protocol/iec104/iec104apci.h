﻿#ifndef IEC104APCI_H
#define IEC104APCI_H

#include <mybase.h>

class IEC104Control : public MyBase
{
public:
	IEC104Control(const MyConfig& Config);
	~IEC104Control();
	virtual bool init(const QByteArray& buff);
	virtual bool createData(MyData& proData);

public:
	uchar type;		//帧类型
	uchar code;		//功能码
	ushort remoteSendNo;	//对端接收序号
	ushort remoteRecvNo;	//对端发送序号
	ushort localSendNo;		//本地接收序号
	ushort localRecvNo;		//本地发送序号
};

class IEC104Apci : public MyBase
{
public:
	IEC104Apci(const MyConfig& Config);
	~IEC104Apci();
	virtual bool init(const QByteArray& buff);
	virtual bool handle(const QByteArray& buff);				//单独处理多出来的数据
	virtual QString showToText();
	virtual bool createData(MyData& proData);

public:
	uchar first;
	ushort length;
	IEC104Control control;

};

#endif // IEC104APCI_H
