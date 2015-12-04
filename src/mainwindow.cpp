#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QRect>
#include <QFileSystemModel>

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

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(splitterB);

    QRect rect = qApp->desktop()->availableGeometry();
    setGeometry(rect.width() / 10, rect.height() / 5, rect.width() / 1.5, rect.height() / 1.5);

    QWidget *window = new QWidget();
    window->setLayout(layout);
    setCentralWidget(window);

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::homePath());
    ui->tvNavBar->setModel(model);
    ui->tvNavBar->setRootIndex(model->index(QDir::homePath()));
    ui->tvNavBar->hideColumn(1);
    ui->tvNavBar->hideColumn(2);
    ui->tvNavBar->hideColumn(3);
}

MainWindow::~MainWindow()
{
    delete ui;
}
