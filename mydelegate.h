// TP4-5/EX1/mydelegate.h
// Exercice 1 : Formulaire emploi du temps
// BODIN Maxime C2
// 08/04/2022

#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QItemDelegate>
#include <QObject>
#include <QModelIndex>
#include <QSize>
#include <QComboBox>

class MyDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit MyDelegate(QObject *parent = 0);

    // Create Editor when we construct MyDelegate
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    // Then, we set the Editor
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    // When we modify data, this model reflect the change
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    // Give the SpinBox the info on size and location
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

};

#endif // MYDELEGATE_H
