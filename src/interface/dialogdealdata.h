#ifndef DIALOGDEALDATA_H
#define DIALOGDEALDATA_H

#include <QDialog>

namespace Ui
{
	class DialogDealData;
}

class DialogDealData : public QDialog
{
	Q_OBJECT

public:
	explicit DialogDealData(QWidget *parent = nullptr);
	~DialogDealData();
private slots:
	void on_pbcrc_clicked();

	void on_pbtransform_clicked();

	void on_Bt1_clicked();

	void on_Bt2_clicked();

	void on_Bt3_clicked();

	void on_Bt4_clicked();


	void on_Bt_clear_clicked();

private:
	void initfrom();

private:
	Ui::DialogDealData *ui;
};

#endif // DIALOGDEALDATA_H
