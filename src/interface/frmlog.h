#ifndef FRMLOG_H
#define FRMLOG_H

#include <QListWidgetItem>
#include <QWidget>
#include <mybase.h>

namespace Ui
{
class frmLog;
}

class frmLog : public QWidget
{
	Q_OBJECT

public:
	explicit frmLog(QWidget *parent = nullptr);
	~frmLog();

public slots:
	void handleLog(const MyLog& log);

private slots:
	void on_listWidget_itemActivated(QListWidgetItem *item);

	void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
	Ui::frmLog *ui;
};

#endif // FRMLOG_H
