#ifndef MANAGERIEC104MASTER_H
#define MANAGERIEC104MASTER_H

#include "promanager.h"

#include <iec104.h>

class ManagerIEC104Master : public ProManager
{
	Q_OBJECT
public:
	ManagerIEC104Master();
	~ManagerIEC104Master();

	virtual bool start();
	virtual void timerRcv();
	virtual void timerSnd();

	void setAsduAddr(uint addr);

	QByteArray SendU(uchar ch);
	QByteArray SendS();
	QByteArray SendI(const QByteArray& data);

	QByteArray asdu100Create();
public:
	IEC104 protocolShow;
private:
	IEC104 my104;
	uint asduAddr;
	int noDataTimes;
	bool sSend;			//可以发送S帧
	ushort sndNo;		//发送序号
	ushort rcvNo;		//接收序号
	ushort k;		//未被确认I报文最大数目
	ushort w;		//最迟确认I报文最大数目
};

#endif // MANAGERIEC104MASTER_H
