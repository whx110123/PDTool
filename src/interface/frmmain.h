#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <mybase.h>
#include "globaldefine.h"
#include "dlgmodbus.h"
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
	DlgModbus *modbusdlg;
	int currentIndex;
	QTextCursor tc;
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
	void on_action_SendData_triggered(bool checked);





	void on_action_TCPClient_triggered();

	void on_action_TCPServer_triggered();

	void on_action_UDPClient_triggered();

	void on_action_UDPServer_triggered();

	void on_action_COM_triggered();

	void on_action_Analys_triggered();

	void on_action_IEC104Master_triggered(bool checked);

	void on_action_MeasuredTerminalMaster_triggered(bool checked);

	void on_action_lightblue_triggered();

	void on_action_flatwhite_triggered();

	void on_action_psblack_triggered();

	void on_action_Update_triggered();

	void on_action_Exit_triggered();

	void on_pushButton_before_clicked();

	void on_pushButton_after_clicked();

	void on_action_About_triggered();

	void on_action_wiscom_triggered();

	void on_action_Log_triggered();

public:
	MyBase *createByName(QString name);
	void SaveAll();
	MyConfig initProtocolConfig();
	void ConfigHide();
	void ActionHide();
	void ConfigShow(int index);
	void initcursor();

};

#endif // FRMMAIN_H
