#ifndef MANAGERMTMASTER_H
#define MANAGERMTMASTER_H

#include "promanager.h"

#include <measuredterminal.h>

class ManagerMTMaster : public ProManager
{
	Q_OBJECT
public:
	explicit ManagerMTMaster(const MyConfig& Config);
	~ManagerMTMaster();

	virtual void timerRcv();
	virtual void timerSnd();

	void setAddr(uint a1, uint a2, uchar a3);

	QByteArray SendAFN(const QByteArray& data);
	uchar createCode(uchar afn);
	QByteArray afn2Create();

public:
	MeasuredTerminal protocolShow;
private:
	MeasuredTerminal myMT;
	uint A1;				//省地市区县码
	uint A2;				//终端地址
	uchar A3;				//主站地址
	uchar fcb;
	uchar pseq;
	int noDataTimes;
	MyConfig mConfig;
};

#endif // MANAGERMTMASTER_H
