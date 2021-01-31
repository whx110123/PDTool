#ifndef PROMANAGER_H
#define PROMANAGER_H

#include "dataconfig.h"
#include "functotext.h"

class ProManager : public QObject
{
	Q_OBJECT
public:
	ProManager();
	~ProManager();

	void init();
	virtual bool start();
	virtual bool stop();
	void setProName(const QString& name);
	void setMaster(bool Master);
	void setRcvData(const QByteArray& data);
	void addRcvData(const QByteArray& data);
	void addSndData(const QByteArray& data);
	void clearData();

	virtual void timerRcv();
	virtual void timerSnd();

signals:
	void Send(const QByteArray& data);
	void toText(const QString& text, int type);			//报文的解析,type 0接收 1发送
	void toLog(const QString& text);					//发送报告

public:
	uint flag;						//状态标识
	QString protocolName;
	bool isMaster;
	bool isRun;
	QByteArray rcvData;
	QVector<QByteArray> sndDatas;

	QTimer *handleRcvDataTimer;
	QTimer *handleSndDataTimer;

};

#endif // PROMANAGER_H
