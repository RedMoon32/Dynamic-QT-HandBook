#include "combobox.h"

#include <QComboBox>
#include <QDebug>
#include "datamodel.h"
#include "tabledatamodel.h"

/**
 * @brief Combobox to display available options in
 * qtableview if some property is TableAttributable*,
 * in this case it will get properties class (for example Country)
 * append _List, and get Country_List - list of countries from datamodel
 * @param d - DataModel to get list for combobox info and retreive primary-attribue
 * (for Country e.g. show Country-Names in combolist)
 * @param td - TableDataModel to get current array of rows from table
 */
ComboBoxItemDelegate::ComboBoxItemDelegate(QObject *parent, DataModel* d, TableDataModel* td)
    : QStyledItemDelegate(parent), m_dataModel(d), m_tableDataModel(td)
{
}


QWidget *ComboBoxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
      Q_UNUSED(option);
      QComboBox *cb = new QComboBox(parent);
      auto prop_name = m_tableDataModel->headerData(index.column(),Qt::Horizontal,Qt::DisplayRole).toString();
      auto list = m_tableDataModel->getData();
      if (list.length()==0)
          return cb;
      auto comp_attribute_type = list[0]->property(prop_name.toLocal8Bit()).typeName();
      QString q = comp_attribute_type;
      // Get dynamically list from dataModel
      // (eg Country_List to show country names if property is Country)
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
