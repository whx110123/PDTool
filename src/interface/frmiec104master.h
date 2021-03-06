﻿#ifndef FRMIEC104MASTER_H
#define FRMIEC104MASTER_H

#include <manageriec104master.h>
#include <mybase.h>

namespace Ui
{
class frmIEC104Master;
}

class frmIEC104Master : public QWidget
{
	Q_OBJECT

public:
	explicit frmIEC104Master(QWidget *parent = nullptr);
	~frmIEC104Master();

private:
	void initfrm();
	void init();
	void initConfig();

signals:
	void ToTcpClient(const QString& data);
	void ToTcpServer(const QString& data);
	void ToUdpClient(const QString& data);
	void ToUdpServer(const QString& data);
	void ToCom(const QString& data);

	void toLog(const MyLog& log);

public slots:
	void dealRcvData(const QString& data, const QString& title);

private slots:
	void sendData(const QByteArray& data);
	void startdebug();
	void stopdebug();
	void handleLog(MyLog& log);					//处理日志
	void emitsignals(const QString& data);				//发送报文到网口与串口
	void showRemoteResult(const QString& data);
	IEC101AsduData *getYKYTData(uchar type);			//type 0x00执行 0x80选择

	void on_pushButton_Start_clicked();					//开始模拟

	void on_pushButton_SendUStart_clicked();			//启动链路

	void on_pushButton_SendUTest_clicked();				//发送测试

	void on_pushButton_SendS_clicked();					//发送确认

	void on_pushButton_CallAll_clicked();				//总召

	void on_pushButton_SetTime_clicked();				//对时

	void on_pushButton_CallTitle_clicked();				//召唤组标题

	void on_pushButton_CallUnit_clicked();				//召唤量纲

	void on_pushButton_CallAccuracy_clicked();			//召唤精度

	void on_pushButton_CallRange_clicked();				//召唤量程

	void on_pushButton_CallDescription_clicked();		//召唤描述

	void on_pushButton_SelectSetting_clicked();			//选择定值区

	void on_pushButton_CallSetting_clicked();			//召唤定值

	void on_pushButton_SetValue_clicked();				//修改定值

	void on_pushButton_solidify_clicked();				//固化定值

	void on_comboBox_RemoteType_currentIndexChanged(const QString& arg1);

	void on_pushButton_Select_clicked();

	void on_pushButton_Execute_clicked();

	void on_pushButton_Cancel_clicked();

	void on_checkBox_isHex_stateChanged(int arg1);

	void on_pushButton_SendAsdu1_clicked();

	void on_pushButton_SendAsdu2_clicked();

	void on_pushButton_SendAsdu3_clicked();

	void on_pushButton_SendAsdu4_clicked();

	void on_pushButton_SendAsdu5_clicked();

	void on_pushButton_SendAsdu6_clicked();

private:
	Ui::frmIEC104Master *ui;
	ManagerIEC104Master *manager;
	ConfigIEC104Master managerConfig;		//参数配置
	MyConfig config;						//报文格式
	uchar myngd;

};

#endif // FRMIEC104MASTER_H
