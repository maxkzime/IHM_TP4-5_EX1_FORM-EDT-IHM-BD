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


//#include <QSplitter>
//#include <QFileSystemModel>
//#include <QTreeView>
//#include <QListView>
/*
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplitter *splitter = new QSplitter;

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    QTreeView *tree = new QTreeView(splitter);
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));

    QListView *list = new QListView(splitter);
    list->setModel(model);
    list->setRootIndex(model->index(QDir::currentPath()));

    splitter->setWindowTitle("Two views onto the same file system model");
    splitter->show();
    return app.exec();
}*/
