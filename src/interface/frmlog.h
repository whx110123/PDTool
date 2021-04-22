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
	void clearlist();

private slots:
	void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

	void on_listWidget_customContextMenuRequested(const QPoint& pos);

private:
	Ui::frmLog *ui;
	QMenu *popMenu;
	QAction *clearSeeds;
};

#endif // FRMLOG_H
