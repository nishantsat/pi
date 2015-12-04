#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->addAction("Run");

    // Add the input and output screens
    QSplitter* splitterA = new QSplitter();
    splitterA->setOrientation(Qt::Vertical);
    splitterA->addWidget(ui->txtInput);
    splitterA->addWidget(ui->txtOutput);
    ui->txtOutput->setStyleSheet("QTextEdit {background-color: black;}");
    ui->txtOutput->setTextColor(QColor("white"));
    ui->txtOutput->setText("[Ready]");

    QSizePolicy policyA;
    policyA.setHorizontalStretch(1);
    QSizePolicy policyB;
    policyB.setHorizontalStretch(4);
    QSplitter* splitterB = new QSplitter();
    ui->tvNavBar->setSizePolicy(policyA);
    splitterA->setSizePolicy(policyB);
    splitterB->addWidget(ui->tvNavBar);
    splitterB->addWidget(splitterA);
    ui->tvNavBar->resize(50, ui->tvNavBar->height());

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(splitterB);

    QWidget *window = new QWidget();
    window->setLayout(layout);
    setCentralWidget(window);
}

MainWindow::~MainWindow()
{
    delete ui;
}
