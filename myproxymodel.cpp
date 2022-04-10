// TP4-5/EX1/myproxymodel.cpp
// Exercice 1 : Formulaire emploi du temps
// BODIN Maxime C2
// 08/04/2022

#include "myproxymodel.h"

MyProxyModel::MyProxyModel(QObject *parent): QSortFilterProxyModel(parent),
    itsValue(0.0)
{}


bool MyProxyModel::filterAcceptsRow(int source_row,
                                    const QModelIndex &source_parent) const
{
    bool validation = false;
    QModelIndex indC = sourceModel()->index(source_row,4, source_parent);
    QModelIndex indD = sourceModel()->index(source_row,3, source_parent);

    if(sourceModel()->data(indD).toDouble() == itsValue)
        validation = true;

    if(sourceModel()->data(indC) == itsClassroom)
        validation = true;

    return validation;
}


QVariant MyProxyModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const {
    return sourceModel()->headerData(section,
                                     orientation,
                                     role);
}


void MyProxyModel::setValue(double value)
{
    itsValue = value;
    invalidateFilter();
}


void MyProxyModel::setClassroom(QString cr)
{
    itsClassroom = cr;
    invalidateFilter();
}
