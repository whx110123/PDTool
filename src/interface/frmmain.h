#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <mybase.h>
#include "globaldefine.h"
#include "dialogmodbus.h"
#include "myhighlighter.h"

namespace Ui
{
class frmMain;
}

class frmMain : public QMainWindow
{
	Q_OBJECT

public:
	explicit frmMain(QWidget *parent = 0);
	~frmMain();

protected:
	bool eventFilter(QObject *obj, QEvent *ev) override;

private:
	Ui::frmMain *ui;
	myhighlighter *highlighter1;
	myhighlighter *highlighter2;
	DialogModbus *modbusdlg;
private slots:
	void initForm();
	void initSignalAndSlots();
	void initStyle();
	void initTranslator();

	void on_clearBtn_clicked();

	void on_protocolcbox_currentIndexChanged(const QString& arg1);

	void on_highlightEdit_textChanged(const QString& arg1);

	void on_fontcolor_clicked();

	void on_backgroundcolor_clicked();

	void on_fontchange_clicked();

	void on_pushButton_Analysis_clicked();

	void on_pushButton_change_clicked();

	void on_pushButton_clean_clicked();

	void on_pushButton_hide_clicked();

	void on_pushButton_clicked();

	void on_action_HandleData_triggered(bool checked);
	void on_action_Config_triggered(bool checked);

	void on_pbcrc_clicked();

	void on_pbtransform_clicked();

	void on_Bt1_clicked();

	void on_Bt2_clicked();

	void on_Bt3_clicked();

	void on_Bt4_clicked();

	void on_Bt_clear_clicked();



	void on_action_TCPClient_triggered();

	void on_action_TCPServer_triggered();

	void on_action_UDPClient_triggered();

	void on_action_UDPServer_triggered();

	void on_action_COM_triggered();

	void on_action_Analys_triggered();

public:
	MyBase *createByName(QString name);
	void SaveAll();
	void initProtocolConfig();
	void ConfigHide();
	void ConfigShow(int index);

};

#endif // FRMMAIN_H
