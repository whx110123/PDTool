#ifndef FRMHANDLEDATA_H
#define FRMHANDLEDATA_H

#include <QWidget>
#include "globaldefine.h"
namespace Ui
{
class frmHandleData;
}

class frmHandleData : public QWidget
{
	Q_OBJECT

public:
	explicit frmHandleData(QWidget *parent = nullptr);
	~frmHandleData();
private slots:
	void on_pbcrc_clicked();

	void on_pbtransform_clicked();

	void on_Bt1_clicked();

	void on_Bt2_clicked();

	void on_Bt3_clicked();

	void on_Bt4_clicked();

	void on_Bt_clear_clicked();

	void on_checkreverse_stateChanged(int arg1);

private:
	void initForm();

private:
	Ui::frmHandleData *ui;
};

#endif // FRMHANDLEDATA_H
