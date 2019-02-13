#ifndef DIALOGSTART_HH
#define DIALOGSTART_HH

#include <QDialog>

namespace Ui {
class DialogStart;
}

class DialogStart : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStart(QWidget *parent = 0);
    ~DialogStart();

    int getMoney();

private slots:
    void configMoney();

private:
    Ui::DialogStart *ui;

    int _money;
};

#endif // DIALOGSTART_HH
