#ifndef DIALOGPMA_H
#define DIALOGPMA_H

#include <QDialog>
#include <iec104.h>

namespace Ui
{
	class DialogPMA;
}

class DialogPMA : public QDialog
{
	Q_OBJECT

public:
	explicit DialogPMA(QWidget *parent = nullptr);
	~DialogPMA();
public slots:
	void dealData(const QString& data, const QString& title);
	bool createAndSendData(IECDataConfig& config);
signals:

	void dlgTotcpclient(const QString& data);
	void dlgTotcpserver(const QString& data);
	void dlgToudpclient(const QString& data);
	void dlgToudpserver(const QString& data);
	void dlgTocom(const QString& data);
private slots:
	void init();
	void handleData();
	void startdebug();
	void stopdebug();
	void showToText(QByteArray ba);
	void emitsignals(const QString& data);
	QByteArray getYKYTData(uchar type);

	void on_pushButton_start_clicked();

	void on_pushButton_sendasdu_clicked();

	void on_pushButton_104callTitle_clicked();			//召唤组标题

	void on_pushButton_104callRange_clicked();			//召唤量程

	void on_pushButton_104callDescription_clicked();	//召唤定值描述

	void on_pushButton_104callAccuracy_clicked();		//召唤定值精度

	void on_pushButton_104callDimension_clicked();		//召唤定值量纲

	void on_pushButton_104callSetting_clicked();


	void on_pushButton_104setFloatDowm_clicked();

	void on_pushButton_104settingCuring_clicked();

	void on_pushButton_104setUintDowm_clicked();


	void on_pushButton_clear_clicked();

	void on_pushButton_104select_clicked();

	void on_pushButton_104execute_clicked();

	void on_pushButton_104cancel_clicked();

	void on_checkBox_104isHex_stateChanged(int arg1);

	void on_pushButton_reflash_clicked();

	void on_pushButton_104sendUstart_clicked();

	void on_pushButton_104sendS_clicked();

	void on_pushButton_104sendUtest_clicked();

	void on_pushButton_104callall_clicked();

	void on_pushButton_sendasdu_2_clicked();

	void on_pushButton_sendasdu_3_clicked();

	void on_pushButton_sendasdu_4_clicked();

	void on_pushButton_sendasdu_5_clicked();

	void on_pushButton_sendasdu_6_clicked();

	void on_pushButton_104setTime_clicked();

private:
	Ui::DialogPMA *ui;
	MyBase *mProtocol;
	MyBase *mProtocolShow;
	IECDataConfig config;
	QTimer *handleDataTimer;
	QByteArray recvData;
	bool haveData;
};

#endif // DIALOGPMA_H
