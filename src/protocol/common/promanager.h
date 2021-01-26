#ifndef PROMANAGER_H
#define PROMANAGER_H

#include "dataconfig.h"
#include "functotext.h"

class ProManager
{
public:
	ProManager();
	~ProManager();

	void setProName(const QString& name);
	void setMaster(bool Master);
	void setData(const QByteArray& data);
	void addData(const QByteArray& data);
	void clearData();
private:
	QString protocolName;
	bool isMaster;
	QByteArray dataAll;

};

#endif // PROMANAGER_H
