#ifndef DLGINTRODUCTION_H
#define DLGINTRODUCTION_H

#include <QDialog>

namespace Ui
{
class DlgIntroduction;
}

class DlgIntroduction : public QDialog
{
	Q_OBJECT

public:
	explicit DlgIntroduction(QWidget *parent = nullptr);
	~DlgIntroduction();

private:
	Ui::DlgIntroduction *ui;
};

#endif // DIALOGINTRODUCTION_H
