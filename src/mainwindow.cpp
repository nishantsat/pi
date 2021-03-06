#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSplitter>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QRect>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QList>
#include <QKeyEvent>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    installEventFilter(this);
    ui->setupUi(this);
    ui->txtInput->setStyleSheet("QTextEdit {background-color: white;}");
    ui->txtInput->setTextColor(QColor("black"));
    ui->txtInput->setText("");

    ui->txtOutput->setStyleSheet("QTextEdit {background-color: black;}");
    ui->txtOutput->setTextColor(QColor("white"));
    ui->txtOutput->setText("_");

    ui->twNavBar->setHeaderLabel("");


    QSplitter* sb = new QSplitter(Qt::Vertical);
    sb->addWidget(ui->tabWx);
    ui->tabWx->addTab(ui->txtInput, "new *");
    sb->addWidget(ui->txtOutput);
    QList<int> sz;
    sz << 10 << 10;
    sb->setSizes(sz);

    QSplitter* sa = new QSplitter(Qt::Horizontal);
    sa->addWidget(ui->twNavBar);
    sa->addWidget(sb);

    sb->setStretchFactor(0, 10);
    sb->setStretchFactor(1, 1);
    sa->setStretchFactor(0, 1);
    sa->setStretchFactor(1, 3);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(sa);
    QWidget* widget = new QWidget();
    widget->setLayout(layout);
    setCentralWidget(widget);

    QRect rect = qApp->desktop()->availableGeometry();
    setGeometry(rect.width() / 10, rect.height() / 5, rect.width() / 1.5, rect.height() / 1.5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    (void)obj;
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_F12) {
            QString qs = ui->txtInput->toPlainText();
            std::string input = qs.toUtf8().constData();
            auto first = begin(input);
            auto last = end(input);

            auto val = 0.0;
            auto isSuccess  = qi::phrase_parse(first, last,
              parser, qi::space, val);

            if (first != last || !isSuccess)
              ui->txtOutput->setText("Error: Parse error. ");
            else
              ui->txtOutput->setText(QString::number(val));
            return true;
        }
    }
    return false;
}

void MainWindow::on_actionNew_triggered()
{
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open pi Project"), QDir::homePath() + "/stuff/pi", tr("Pi Project Files (*.piproj)"));
    readProjectFile(fileName);
}

void MainWindow::readProjectFile(QString filename)
{
    // Sample project file (JSON format)
    // {
    //     "files": ["a.pi", "b.pi"]
    // }

    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();

    // Extract project name
    QString projectName = filename;
    projectName.chop(7); // because .piproj is 7 letters
    QStringList parts = projectName.split('/');
    projectName = parts[parts.length() - 1];

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonValue value = d.object().value(QString("files"));
    QTreeWidgetItem *proj = new QTreeWidgetItem(ui->twNavBar);
    proj->setText(0, projectName);

    QJsonArray files = value.toArray();
    QStringList list;
    foreach (const QJsonValue& v, files) {
        list << v.toString();
        QTreeWidgetItem* item = new QTreeWidgetItem(proj);
        item->setText(0, v.toString());
    }
    ui->twNavBar->expandAll();
}

void MainWindow::on_twNavBar_doubleClicked(const QModelIndex &index)
{
    QString s = index.data().toString();
    auto itr = tabs.find(s.toStdString());
    if (itr != tabs.end())
        return;
    QTextEdit* te = new QTextEdit();
    ui->tabWx->addTab(te, s);
    tabs[s.toStdString()] = te;
}

void MainWindow::on_tabWx_tabCloseRequested(int index)
{
    std::string title = ui->tabWx->tabText(index).toStdString();
    ui->tabWx->removeTab(index);
    auto itr = tabs.find(title);
    if (itr != tabs.end()) {
        if (itr->second != nullptr)
            delete itr->second;
        tabs.erase(tabs.find(title));
    }
}
