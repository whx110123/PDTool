﻿#ifndef FRMMEASUREDTERMINALMASTER_H
#define FRMMEASUREDTERMINALMASTER_H

#include <QWidget>
#include <mybase.h>

namespace Ui
{
class frmMeasuredTerminalMaster;
}

class frmMeasuredTerminalMaster : public QWidget
{
	Q_OBJECT

public:
	explicit frmMeasuredTerminalMaster(QWidget *parent = nullptr);
	~frmMeasuredTerminalMaster();
private:
	void initfrm();
	void init();
	MyConfig initConfig();

signals:
	void ToTcpClient(const QString& data);
	void ToTcpServer(const QString& data);
	void ToUdpClient(const QString& data);
	void ToUdpServer(const QString& data);
	void ToCom(const QString& data);

public slots:
	void dealRcvData(const QString& data, const QString& title);
private slots:
	void sendData(const QByteArray& data);
	void startdebug();
	void stopdebug();
	void showToText(const QString& data, int type);		//type 0接收 1发送
	void showLog(const QString& data);
	void emitsignals(const QString& data);

private:
	Ui::frmMeasuredTerminalMaster *ui;
};

#endif // FRMMEASUREDTERMINALMASTER_H
