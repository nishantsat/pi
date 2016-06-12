#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QRect>
#include <QFileDialog>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add the input and output screens
    QSplitter* splitterA = new QSplitter();
    splitterA->setOrientation(Qt::Vertical);
    splitterA->addWidget(ui->txtInput);
    splitterA->addWidget(ui->txtOutput);
    ui->txtOutput->setStyleSheet("QTextEdit {background-color: black;}");
    ui->txtOutput->setTextColor(QColor("white"));
    ui->txtOutput->setText("[Ready]");
    ui->twNavBar->setHeaderLabel("");

    QSizePolicy policyA;
    policyA.setHorizontalStretch(1);
    QSizePolicy policyB;
    policyB.setHorizontalStretch(4);
    QSplitter* splitterB = new QSplitter();
    ui->twNavBar->setSizePolicy(policyA);
    splitterA->setSizePolicy(policyB);
    splitterB->addWidget(ui->twNavBar);
    splitterB->addWidget(splitterA);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(splitterB);

    QRect rect = qApp->desktop()->availableGeometry();
    setGeometry(rect.width() / 10, rect.height() / 5, rect.width() / 1.5, rect.height() / 1.5);

    QWidget *window = new QWidget();
    window->setLayout(layout);
    setCentralWidget(window);

    ui->txtInput->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
}

void MainWindow::on_actionOpen_triggered()
{
    qDebug() << "In";
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open pi Project"), QDir::homePath() + "/stuff/pi", tr("Pi Project Files (*.piproj)"));
    readJson(fileName);
}

void MainWindow::readJson(QString filename)
{
    /* Sample project file (which is in JSON format)
        {
           "files": {
               "sources":["a.pi","b.pi"]
           }
        }
    */

    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("files"));
    QJsonObject item = value.toObject();

    // Extract project name
    QString projectName = filename;
    projectName.chop(7); // because .piproj is 7 letters
    QStringList parts = projectName.split('/');
    projectName = parts[parts.length() - 1];
    //ui->twNavBar->setHeaderLabel(projectName);

    QTreeWidgetItem *proj = new QTreeWidgetItem(ui->twNavBar);
    proj->setText(0, projectName);

    QJsonArray files = item["sources"].toArray();
    QStringList list;
    foreach (const QJsonValue& v, files) {
        list << v.toString();
        QTreeWidgetItem* item = new QTreeWidgetItem(proj);
        item->setText(0, v.toString());
    }
    ui->twNavBar->expandAll();
    /*
    // setup navbar
    QStringListModel *model = new QStringListModel();
    model->setStringList(list);
    ui->tvNavBar->setModel(model);
    */
}
