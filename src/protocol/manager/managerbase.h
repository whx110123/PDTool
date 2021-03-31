#ifndef MANAGERBASE_H
#define MANAGERBASE_H

#include "dataconfig.h"
#include "functotext.h"

class ManagerConfig
{
public:
	ManagerConfig();
	~ManagerConfig();
	QString protocolName;
	bool isMaster;
};

class ManagerBase : public QObject
{
	Q_OBJECT
public:
	ManagerBase();
	~ManagerBase();

	void init();
	virtual bool start();
	virtual bool stop();
	virtual void restoreDefaults();
	void initConfig(ManagerConfig *config);
	virtual void initMyConfig(ManagerConfig *config);

	void addRcvData(const QByteArray& data);
	void addSndData(const QByteArray& data);
	void clearData();

	virtual void timerRcv();
	virtual void timerSnd();

signals:
	void Send(const QByteArray& data);
	void toText(const QString& text, int type);			//报文的解析,type 0接收 1发送
	void toLog(const QString& text);					//发送报告

	void handleData();

public:

	uint flag;						//状态标识
	QString protocolName;
	bool isMaster;
	bool isRun;
	QMutex mutexRD;
	QByteArray rcvData;
	QMutex mutexSD;
	QVector<QByteArray> sndDatas;
	QTimer *handleRcvDataTimer;
	QTimer *handleSndDataTimer;

};

#endif // MANAGERBASE_H
