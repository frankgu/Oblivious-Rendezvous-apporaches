#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "algorithms.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_IDHopping_clicked();

    void on_confirmInput_clicked();

    void on_MultiStepHopping_clicked();

    void on_ModifiedModuleClock_clicked();

    void on_confirm_clicked();

private:
    Ui::MainWindow *ui;
    algorithms alg;
    int currentAlgorithm;
};

#endif // MAINWINDOW_H
