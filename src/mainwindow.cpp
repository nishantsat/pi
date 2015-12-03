#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->addAction("Run");
    ui->tvNavBar->setMinimumWidth(100);
    ui->tvNavBar->setMaximumWidth(200);

    ui->txtOutput->setStyleSheet("QTextEdit {background-color: black;}");
    ui->txtOutput->setTextColor(QColor("white"));
    ui->txtOutput->setText("Hello");
}

MainWindow::~MainWindow()
{
    delete ui;
}
