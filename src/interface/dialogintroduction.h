#ifndef DIALOGINTRODUCTION_H
#define DIALOGINTRODUCTION_H

#include <QDialog>

namespace Ui
{
	class DialogIntroduction;
}

class DialogIntroduction : public QDialog
{
	Q_OBJECT

public:
	explicit DialogIntroduction(QWidget *parent = nullptr);
	~DialogIntroduction();

private:
	Ui::DialogIntroduction *ui;
};

#endif // DIALOGINTRODUCTION_H
