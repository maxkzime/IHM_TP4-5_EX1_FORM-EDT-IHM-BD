// TP4-5/EX1/mydelegate.cpp
// Exercice 1 : Formulaire emploi du temps
// BODIN Maxime C2
// 08/04/2022

#include "mydelegate.h"


MyDelegate::MyDelegate(QObject *parent) :
    QItemDelegate(parent)
{}


// TableView need to create an Editor
// Create Editor when we construct MyDelegate
// and return the Editor
QWidget* MyDelegate::createEditor(QWidget *parent,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    Q_UNUSED(&option);
    Q_UNUSED(&index);

    QComboBox  *editor = new QComboBox (parent);
    editor->addItem("CM");
    editor->addItem("TP");
    editor->addItem("TD");
    editor->setInsertPolicy(QComboBox::NoInsert);

    return editor;
}


// Then, we set the Editor
// Gets the data from Model and feeds the data to Editor
void MyDelegate::setEditorData(QWidget *editor,
                               const QModelIndex &index) const
{
    // Get the value via index of the Model
    int value = index.model()->data(index, Qt::EditRole).toUInt();

    // Put the value into the ComboBox
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentIndex(comboBox->findData(value));
}


// When we modify data, this model reflect the change
// Data from the delegate to the model
void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    model->setData(index, comboBox->itemText(comboBox->currentIndex()), Qt::EditRole);
}


// Give the SpinBox the info on size and location
void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(&index);

    editor->setGeometry(option.rect);
}
