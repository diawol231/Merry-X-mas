#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include <QPixmap>
#include <QPalette>
#include <QTimer>
#include <garland.h>
#include <iostream>
#include <QDebug>
#include <QBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    int girland1 = 5,
    girland2 = 4,
    girland3 = 3;

    std::vector<int> paintButArr1;
    std::vector<int> paintButArr2;
    std::vector<int> paintButArr3;
    QList<QPushButton *> *buttons1, *buttons2, *buttons3;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer* qTimeToLight;
    void paintGarland1();
    void paintGarland2();
    void paintGarland3();
    void arrayButtons();

private slots:
    void on_starterButt_clicked();
    void lightTime();

    void on_stoperButt_clicked();

    void on_switcher3_stateChanged(int arg1);

    void on_switcher1_stateChanged(int arg1);

    void on_switcher2_stateChanged(int arg1);

    void on_algrSwitch1_clicked();

    void on_algrSwitch2_clicked();

    void on_algrSwitch3_clicked();

private:
    Ui::MainWindow *ui;
    Garland garl_1, garl_2, garl_3;

};
#endif // MAINWINDOW_H
