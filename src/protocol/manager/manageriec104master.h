﻿#ifndef MANAGERIEC104MASTER_H
#define MANAGERIEC104MASTER_H

#include "managerbase.h"

#include <iec104.h>

class ConfigIEC104Master: public ManagerConfig
{
public:
	ConfigIEC104Master();
	~ConfigIEC104Master();
public:
	uint asduAddr;

};

class ManagerIEC104Master : public ManagerBase
{
	Q_OBJECT
public:
	explicit ManagerIEC104Master(const MyConfig& Config);
	~ManagerIEC104Master();

	virtual void restoreDefaults();
	virtual void timerRcv();
	virtual void timerSnd();
	virtual void initMyConfig(ManagerConfig *config);

	QByteArray SendU(uchar ch);
	QByteArray SendS();
	QByteArray SendI(const QByteArray& data);

	QByteArray asdu100Create();
	QByteArray asdu103Create();
public slots:
	void update();

public:
	IEC104 protocolShow;

private:
	QTimer *SecondTimer;
	IEC104 myPro;
	uint asduAddr;
	int noDataTimes;
	bool sSend;			//可以发送S帧
	ushort sndNo;		//发送序号
	ushort rcvNo;		//接收序号
	ushort k;			//未被确认I报文最大数目
	ushort w;			//最迟确认I报文最大数目
	MyConfig mConfig;
};

#endif // MANAGERIEC104MASTER_H
