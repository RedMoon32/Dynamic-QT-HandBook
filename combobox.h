#ifndef COMBOBOXITEMDELEGATE_H
#define COMBOBOXITEMDELEGATE_H

#include <QStyledItemDelegate>
#include "datamodel.h"
#include "tabledatamodel.h"

class ComboBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    DataModel *m_dataModel;
    TableDataModel *m_tableDataModel;
public:
    ComboBoxItemDelegate(QObject *parent, DataModel* d, TableDataModel* td);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // COMBOBOXITEMDELEGATE_H
