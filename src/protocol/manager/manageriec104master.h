#ifndef MANAGERIEC104MASTER_H
#define MANAGERIEC104MASTER_H

#include "promanager.h"

class ManagerIEC104Master : public ProManager
{
	Q_OBJECT
public:
	ManagerIEC104Master();
	~ManagerIEC104Master();

	virtual void timerRcv();
	virtual void timerSnd();
};

#endif // MANAGERIEC104MASTER_H
