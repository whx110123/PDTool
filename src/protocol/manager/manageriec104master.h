#ifndef MANAGERIEC104MASTER_H
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
	ushort t1;					//发送或测试APDU的超时
	ushort t2;					//无数据报文时确认的超时，t2<t1。最迟确认I报文时间
	ushort t3;					//长期空闲状态下发送测试帧的超时
	ushort kMax;				//未被确认I报文最大数目
	ushort wMax;				//最迟确认I报文最大数目

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
	void initProConfig(ConfigIEC104Master *config);

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
	int noDataTimes;
	bool sSend;			//可以发送S帧
	ushort sndNo;		//发送序号
	ushort rcvNo;		//接收序号
	ushort k;			//未被确认I报文数目
	ushort w;			//最迟确认I报文数目
	ConfigIEC104Master proConfig;	//规约参数
	MyConfig mConfig;				//报文格式
};

#endif // MANAGERIEC104MASTER_H
