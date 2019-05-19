#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <QTimer>
#include <QWidget>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui -> pushButton_No, SIGNAL(clicked()), this, SLOT(work()));
    connect(ui -> pushButton_Yes, SIGNAL(clicked()), this, SLOT(work()));
    connect(ui -> pushButton_Dont, SIGNAL(clicked()), this, SLOT(work()));
    //connect(ui -> pushButton, SIGNAL(clicked()), this, SLOT(start()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::make_questions(vector <Question>& ref_q) {
    string s;
    unsigned int i = 0;
    QFile file("C:\\NQuestions.txt");
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QString str;
        while(!file.atEnd())
        {
            str = file.readLine();
            string s = str.toLocal8Bit().constData();
            Question a(i, s);
            ref_q.push_back(a);
            ++i;
        }
        file.close();
    }
}

void MainWindow::read_desk(vector <string>& ref_ans) {
    QFile file("C:\\Desk.txt");
    string s;
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QString str;
        while(!file.atEnd())
        {
            str = file.readLine();
            string s = str.toLocal8Bit().constData();
            ref_ans.push_back(s);
        }
        file.close();
    }
    QString qstr = QString::fromStdString(ref_ans[5]);
    ui -> Question -> setText(qstr);
}

void MainWindow::make_characters(vector <string>& ref_ans, vector <Character>& ref_c) {
    unsigned int i = 0;
    QFile file("C:\\NCharacters.txt");
    string s;
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QString str;
        while(!file.atEnd())
        {
            str = file.readLine();
            string s = str.toLocal8Bit().constData();
            Character a(s, ref_ans[i]);
            ref_c.push_back(a);
            ++i;
        }
        file.close();
    }
}

/*void MainWindow::start() {
    vector <Question> q;
    vector <Question>& ref_q = q;
    this -> make_questions(ref_q);
    vector <string> ans;
    vector <string>& ref_ans = ans;
    this -> read_desk(ref_ans);
    vector <Character> c;
    vector <Character>& ref_c = c;
    this -> make_characters(ref_ans, ref_c);
    unsigned int quantity = ref_q.size();
    if (ref_c.size() > 1) {
        Question p = this -> choose_question(ref_c, quantity, ref_q);
        system("pause");
    }
}*/

void MainWindow::work() {
    QPushButton* b = (QPushButton *)sender();
    ui -> Answer -> setStyleSheet("color: rgb(240, 240, 237)");
    ui -> Answer -> setText(b -> text());
}

string MainWindow::help() {
    QString qstr = ui -> Answer -> text();
    string s = qstr.toLocal8Bit().constData();
    return s;
}

Question MainWindow::choose_question(vector <Character>& nes_ch, unsigned int quantity, vector <Question>& ref_q) {
    double k_max = 0;
    unsigned int num = -1;
    for (unsigned int i = 0; i < quantity; ++i) {
        double yes = 0;
        double no = 0;
        for (unsigned int j = 0; j < nes_ch.size(); ++j) {
                char c = nes_ch[j].getAns(i);
                if (c == '1')
                    yes++;
                else
                    no++;
        }
        double d = (yes + no) / (abs(yes - no) + 1);
        if (d > k_max) {
            k_max = d;
            num = i;
        }
    }
    QString qstr = QString::fromStdString(ref_q[num].getText());
    ui -> Question -> setText(qstr);
    QEventLoop loop;
    QTimer timer;
    timer.setInterval(5000); //5 sec
    connect (&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start();
    loop.exec();
    return ref_q[num];
}

void MainWindow::choose_characters(string answer, vector <Character>& nes_ch, Question q) {
    QString qstr = QString::fromStdString(q.getText());
    ui -> Answer -> setText(qstr);
    unsigned int num = q.getNum();
    char c;
    if (answer == "Yes")
        c = '1';
    else {
        if (answer == "No")
            c = '0';
        else {
            if (answer == "Don't undestand")
                c = '_';
        }
    }
    for (int i = nes_ch.size() - 1; i > -1; --i) {
        char s = nes_ch[i].getAns(num);
        if (s != c)
            nes_ch.erase(nes_ch.begin() + i);
    }
}

void MainWindow::right_end(string name) {
    QString qname = QString::fromStdString(name);
    QMessageBox::about(this, "You win!", qname);
    //ui -> Answer -> setStyleSheet("color: rgb(50, 0, 70)");
    //ui -> Answer -> setText(qname);
}

void MainWindow::left_end(){
    QMessageBox::critical(this, "Error", "Opps...");
}
