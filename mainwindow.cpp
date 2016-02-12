#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->n_algorithm5->setVisible(false);
    ui->input_n_algorithm5->setVisible(false);
    ui->confirm->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_IDHopping_clicked()
{
    ui->n_algorithm5->setVisible(false);
    ui->input_n_algorithm5->setVisible(false);
    ui->confirm->setVisible(false);

    ui->M->setValue(0);
    ui->n->setValue(0);
    ui->N->setValue(0);
    ui->ID->setValue(0);
    currentAlgorithm = 1;
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_confirmInput_clicked()
{
    ui->output->clear();
    ui->stackedWidget->setCurrentIndex(0);
    int N = ui->N->value();
    int M = ui->M->value();
    int ID = ui->ID->value();
    int n = ui->n->value();
    QList<int> sequence;
    if(currentAlgorithm == 1) {

        sequence = alg.IDHopping(N,M,ID,n);

    } else if(currentAlgorithm == 2) {

        sequence = alg.MultiStepHopping(ID,N,M,n);

    }
    QString result;
    for (int i = 0; i < sequence.size(); i++)
    {
        result += QString::number(sequence[i]);
        if(i < sequence.size()-1)
           result += "," ;
    }
    ui->output->setText(result);
}

void MainWindow::on_MultiStepHopping_clicked()
{
    ui->n_algorithm5->setVisible(false);
    ui->input_n_algorithm5->setVisible(false);
    ui->confirm->setVisible(false);

    ui->M->setValue(0);
    ui->n->setValue(0);
    ui->N->setValue(0);
    ui->ID->setValue(0);
    currentAlgorithm = 2;
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_ModifiedModuleClock_clicked()
{
    ui->n_algorithm5->setVisible(true);
    ui->input_n_algorithm5->setVisible(true);
    ui->confirm->setVisible(true);
}

void MainWindow::on_confirm_clicked()
{
    ui->output->clear();
    ui->input_n_algorithm5->cleanText();
    int n = ui->input_n_algorithm5->value();

    QList<int> sequence = alg.ModifiedModuleClock(n);
    QString result;
    for (int i = 0; i < sequence.size(); i++)
    {
        result += QString::number(sequence[i]);
        if(i < sequence.size()-1)
           result += "," ;
    }
    ui->output->setText(result);
}
