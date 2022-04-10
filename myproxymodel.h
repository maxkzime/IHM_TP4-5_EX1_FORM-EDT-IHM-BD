// TP4-5/EX1/myproxymodel.h
// Exercice 1 : Formulaire emploi du temps
// BODIN Maxime C2
// 08/04/2022

#ifndef MYPROXYMODEL_H
#define MYPROXYMODEL_H

#include <string>
#include <QSortFilterProxyModel>

using std::string;

class MyProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    MyProxyModel(QObject *parent = nullptr);

    bool filterAcceptsRow(int source_row,
                          const QModelIndex &source_parent) const;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role) const;

public slots:
    void setValue(double value);
    void setClassroom(QString cr);

private:
    double itsValue;
    QString itsClassroom;
};

#endif // MYPROXYMODEL_H
