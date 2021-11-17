#include "mainwindow.h"
#include "ui_mainwindow.h"


QString col[5] = {"background-color: rgb(0,0,0);",   //black
                  "background-color: rgb(0,255,0);", //blue
                  "background-color: rgb(0,0,255);", //green
                  "background-color: rgb(255,91,0);",//orange
                  "background-color: rgb(255,0,0);"};// red

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buttons1 = new QList<QPushButton *>();
    buttons2 = new QList<QPushButton *>();
    buttons3 = new QList<QPushButton *>();

    QPixmap pixmap(":/resource/img/elkaZel.png");
    int w = ui->image->width();
    int h = ui->image->height();
    ui->image->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    ui->stoperButt->setStyleSheet("background-color: rgb(255,0,0);");



    qTimeToLight = new QTimer(this);
    connect(qTimeToLight, SIGNAL(timeout()), this, SLOT(lightTime()));
    qTimeToLight->start(1000);

    arrayButtons();

    QString str = ui->switcher1->objectName();
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::arrayButtons(){

    buttons1->append(ui->girline11);
    buttons1->append(ui->girline12);
    buttons1->append(ui->girline13);
    buttons1->append(ui->girline14);
    buttons1->append(ui->girline15);

    buttons2->append(ui->girline21);
    buttons2->append(ui->girline22);
    buttons2->append(ui->girline23);
    buttons2->append(ui->girline24);

    buttons3->append(ui->girline31);
    buttons3->append(ui->girline32);
    buttons3->append(ui->girline33);

}


void MainWindow::on_starterButt_clicked()
{
    ui->switcher1->setChecked(true);
    ui->switcher2->setChecked(true);
    ui->switcher3->setChecked(true);
}


void MainWindow::paintGarland1(){
    int color = 0;
    for(int i = 0; i < girland1; i++){
        buttons1->at(i)->setStyleSheet(col[paintButArr1[color]]);
        if(color == paintButArr1.size() - 1){
            color = 0;
            continue;
        }
        color++;
    }
}

void MainWindow::paintGarland2(){
    int color = 0;
    for(int i = 0; i < girland2; i++){
        buttons2->at(i)->setStyleSheet(col[paintButArr2[color]]);
        if(color == paintButArr2.size() - 1){
            color = 0;
            continue;
        }
        color++;
    }
}


void MainWindow::paintGarland3(){
    int color = 0;
    for(int i = 0; i < girland3; i++){
        buttons3->at(i)->setStyleSheet(col[paintButArr3[color]]);
        if(color == paintButArr3.size() - 1){
            color = 0;
            continue;
        }
        color++;
    }
}


void MainWindow::lightTime(){
    if(garl_1.isWorked()){
        paintButArr1 = garl_1.getLight();
        paintGarland1();
    }
    else{
        paintButArr1 = garl_1.blackLine();
        paintGarland1();
    }

    if(garl_2.isWorked()){
        paintButArr2 = garl_2.getLight();
        paintGarland2();
    }
    else{
        paintButArr2 = garl_2.blackLine();
        paintGarland2();
    }

    if(garl_3.isWorked()){
        paintButArr3 = garl_3.getLight();
        paintGarland3();
    }
    else{
        paintButArr3 = garl_3.blackLine();
        paintGarland3();
    }

}

void MainWindow::on_stoperButt_clicked()
{
    ui->switcher1->setChecked(false);
    ui->switcher2->setChecked(false);
    ui->switcher3->setChecked(false);

    ui->algrSwitch1->setEnabled(false);
    ui->algrSwitch2->setEnabled(false);
    ui->algrSwitch3->setEnabled(false);

}

void MainWindow::on_switcher1_stateChanged(int arg1)
{
    if(ui->switcher1->isChecked()){
        garl_1.startLight();
        ui->algrSwitch1->setEnabled(true);
    }
    else{
        garl_1.stopWork();
        ui->algrSwitch1->setEnabled(false);
    }
}

void MainWindow::on_switcher2_stateChanged(int arg1)
{
    if(ui->switcher2->isChecked()){
        garl_2.startLight();
        ui->algrSwitch2->setEnabled(true);
    }
    else{
        garl_2.stopWork();
        ui->algrSwitch2->setEnabled(false);
    }
}

void MainWindow::on_switcher3_stateChanged(int arg1)
{
    if(ui->switcher3->isChecked()){
        garl_3.startLight();
        ui->algrSwitch3->setEnabled(true);
    }
    else{
        garl_3.stopWork();
        ui->algrSwitch3->setEnabled(false);
    }
}

void MainWindow::on_algrSwitch1_clicked()
{
    garl_1.inCreaseValue();
}

void MainWindow::on_algrSwitch2_clicked()
{
    garl_2.inCreaseValue();
}

void MainWindow::on_algrSwitch3_clicked()
{
    garl_3.inCreaseValue();
}
