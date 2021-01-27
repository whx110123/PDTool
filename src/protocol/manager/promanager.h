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
	void setProName(const QString& name);
	void setMaster(bool Master);
	void setRcvData(const QByteArray& data);
	void addRcvData(const QByteArray& data);
	void addSndData(const QByteArray& data);
	void clearData();

	virtual void timerRcv();
	virtual void timerSnd();
private:
	QString protocolName;
	bool isMaster;
	QByteArray rcvData;
	QVector<QByteArray> sndDatas;

	QTimer *handleRcvDataTimer;
	QTimer *handleSndDataTimer;

};

#endif // PROMANAGER_H
