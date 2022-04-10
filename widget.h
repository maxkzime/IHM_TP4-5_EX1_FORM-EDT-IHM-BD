// TP4-5/EX1/widget.h
// Exercice 1 : Formulaire emploi du temps
// BODIN Maxime C2
// 08/04/2022

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QtGui>
#include <QMessageBox>
#include <QString>
#include <QDebug>


#include "myproxymodel.h"

using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void populateDataItem();

public slots:
    void addNew();
    void remove();
    void save();
    void activateFilters(int state);


private:
    Ui::Widget *ui;

    QSqlDatabase itsDB;
    QSqlTableModel * itsModel;
    MyProxyModel * itsProxyModel;

    void initDatabase();
    void closeDatabase();

    bool validClassroom();
    bool validDuration();

};
#endif   // WIDGET_H
