#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <unordered_map>

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
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_twNavBar_doubleClicked(const QModelIndex &index);

    void on_tabWx_tabCloseRequested(int index);

private:
    void updateTabbedWindows() const;
    void readProjectFile(QString val);
    Ui::MainWindow *ui;
    std::unordered_map<std::string, QTextEdit*> tabs;
};

#endif // MAINWINDOW_H
