#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    vector <Question> q;
    vector <Question>& ref_q = q;
    w.make_questions(ref_q);
    vector <string> ans;
    vector <string>& ref_ans = ans;
    w.read_desk(ref_ans);
    vector <Character> c;
    vector <Character>& ref_c = c;
    w.make_characters(ref_ans, ref_c);
    unsigned int quantity = ref_q.size();
    string answer;
    w.show();
    while (ref_c.size() > 1) {
        Question p = w.choose_question(ref_c, quantity, ref_q);
        answer = w.help();
        w.choose_characters(answer, ref_c, p);
    }
    if (ref_c.size() == 1)
        w.right_end(ref_c[0].getName());
    else
        w.left_end();
    return a.exec();
}
