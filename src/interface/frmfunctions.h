#ifndef FRMFUNCTIONS_H
#define FRMFUNCTIONS_H

#include <QWidget>
#include "dialogsenddata.h"
#include "dialogdealdata.h"
#include "dialogintroduction.h"
#include "dialogdebug.h"
#include "dialogpma.h"

namespace Ui
{
	class frmFunctions;
}

class frmFunctions : public QWidget
{
	Q_OBJECT

public:
	explicit frmFunctions(QWidget *parent = nullptr);
	~frmFunctions();

private slots:
	void on_pbfunc1_clicked();
	void initfrom();

	void on_pbfunc2_clicked();

	void on_pbintro_clicked();

	void on_pbfunc3_clicked();

	void on_pbfunc4_clicked();

private:
	Ui::frmFunctions *ui;
public:
	DialogSendData *m_dialogsenddata;
	DialogDealData *m_dialogdealdata;
	DialogIntroduction *m_dialogintroduction;
	DialogDebug *m_dialogdebug;
	DialogPMA *m_dialogpma;
};

#endif // FRMFUNCTIONS_H
