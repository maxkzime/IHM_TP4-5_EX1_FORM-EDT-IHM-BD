#include "myproxymodel.h"

MyProxyModel::MyProxyModel(QObject *parent): QSortFilterProxyModel(parent),
    itsValue(0.0)
{}

bool MyProxyModel::filterAcceptsRow(int source_row,
                                    const QModelIndex &source_parent) const
{
    bool validation = false;
    QModelIndex indD = sourceModel()->index(source_row,3, source_parent);

    if(sourceModel()->data(indD).toDouble() == itsValue)
        validation = true;

    return validation;
}

QVariant MyProxyModel::headerData(int section, Qt::Orientation orientation,
                                int role) const {
    return sourceModel()->headerData(section, orientation,
                                     role);
}

void MyProxyModel::setValue(double value)
{
    itsValue = value;
    invalidateFilter();
}
