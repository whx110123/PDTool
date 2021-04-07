#ifndef MANAGERMTMASTER_H
#define MANAGERMTMASTER_H

#include "managerbase.h"

#include <measuredterminal.h>
class ConfigMTMaster: public ManagerConfig
{
public:
	ConfigMTMaster();
	~ConfigMTMaster();
public:
	uint A1;				//省地市区县码
	uint A2;				//终端地址
	uchar A3;				//主站地址
};

class ManagerMTMaster : public ManagerBase
{
	Q_OBJECT
public:
	explicit ManagerMTMaster(const MyConfig& Config);
	~ManagerMTMaster();

	virtual void timerRcv();
	virtual void timerSnd();
	void initProConfig(ConfigMTMaster *config);

	QByteArray SendAFN(const QByteArray& data);
	uchar createCode(uchar afn);
	QByteArray afn2Create(uchar DI0);
	void fcbchange();
public:
	MeasuredTerminal protocolShow;
private:
	MeasuredTerminal myPro;
//	uint A1;				//省地市区县码
//	uint A2;				//终端地址
//	uchar A3;				//主站地址
	uchar fcb;
	uchar pseq;
	int noDataTimes;
	ConfigMTMaster proConfig;
	MyConfig mConfig;
};

#endif // MANAGERMTMASTER_H
