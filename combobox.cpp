#include "combobox.h"

#include <QComboBox>
#include <QDebug>
#include "datamodel.h"
#include "tabledatamodel.h"

ComboBoxItemDelegate::ComboBoxItemDelegate(QObject *parent, DataModel* d, TableDataModel* td)
    : QStyledItemDelegate(parent), m_dataModel(d), m_tableDataModel(td)
{
}

QWidget *ComboBoxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
      Q_UNUSED(option);
      QComboBox *cb = new QComboBox(parent);
      auto prop_name = m_tableDataModel->headerData(index.column(),Qt::Horizontal,Qt::DisplayRole).toString();
      auto comp_attribute_type = m_dataModel->getCompanyList()[0]->property(prop_name.toLocal8Bit()).typeName();
      QString q = comp_attribute_type;
      q = q.left(q.length()-1) + DYNAMIC_LIST_POSTFIX;
      auto value = m_dataModel->property(q.toLocal8Bit());
      auto vlist = value.value<QSequentialIterable>();
      for (const QVariant& v: vlist){
            TableAttributable* dynamic_list_item = qvariant_cast<TableAttributable*>(v);
            if (dynamic_list_item!=nullptr){
                QVariant stored_item;
                stored_item.setValue(dynamic_list_item);
                cb->addItem(dynamic_list_item->getPrimaryAttribute(),stored_item);
             }
      }
      return cb;
}



void ComboBoxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    const QString currentText = index.data(Qt::EditRole).toString();
    const int cbIndex = cb->findText(currentText);
    if (cbIndex >= 0)
       cb->setCurrentIndex(cbIndex);
    else {
        cb->setCurrentIndex(0);
    }
}


void ComboBoxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    model->setData(index, cb->currentData(), Qt::EditRole);
}
