// TP4-5/EX1/main.cpp
// Exercice 1 : Formulaire emploi du temps
// BODIN Maxime C2
// 08/04/2022

#include "widget.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
