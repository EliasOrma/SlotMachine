#include "mainwindow.hh"
#include <QApplication>
#include "dialogstart.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DialogStart dlog;

    if(dlog.exec()== QDialog::Rejected)
    {
        return EXIT_SUCCESS;
    }


    MainWindow w;
    w.addMoney(dlog.getMoney());

    w.show();

    return a.exec();
}
