#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace  std;

namespace Ui {
class MainWindow;
}

class Character {
private:
    string name;
    string ans;
public:
    Character(string name, string ans) {
        this -> name = name;
        this -> ans = ans;
    }
    string getName() {
        return this -> name;
    }
    char getAns(unsigned int c) {
        return (this -> ans)[c];
    }
};

class Question {
private:
    unsigned int num;
    string text;
public:
    Question(unsigned int num, string text) {
        this -> num = num;
        this -> text = text;
    }
    string getText() {
        return this -> text;
    }
    unsigned int getNum() {
        return this -> num;
    }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void make_questions(vector <Question>& ref_q);
    void read_desk(vector <string>& ref_ans);
    void make_characters(vector <string>& ref_ans, vector <Character>& ref_c);
    Question choose_question(vector <Character>& nes_ch, unsigned int quantity, /*const*/ vector <Question>& ref_q);
    void choose_characters(string answer, vector <Character>& nes_ch, Question q);
    string help();
    void right_end(string name);
    void left_end();

private slots:
    void work();
    //void start();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
