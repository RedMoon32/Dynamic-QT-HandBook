#include <QDebug>
#include <QMessageBox>
#include "tabledatamodel.h"

TableDataModel::TableDataModel(QList<TableAttributable*> &dataList, QObject *parent): QAbstractTableModel (parent), m_dataList(dataList)
{
    if ( m_dataList.length()>0){
        headers = m_dataList[0]->getAttributeProperties();
    }
}

int TableDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_dataList.length();
}


int TableDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return headers.length();
}

QVariant TableDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    TableAttributable* comp = m_dataList[index.row()];
    QString property = comp->get_attribute(headers[index.column()].second);
    return property;
}

QVariant TableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return headers[section].second;
    }
    return QVariant();
}

bool TableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
    int row = index.row();
    if (index.isValid() && role == Qt::EditRole && m_dataList[row]->property(headers[index.column()].second)!=value) {
        QMessageBox msgBox;
        msgBox.setText("The row has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Save){
            m_dataList[row]->setProperty(headers[index.column()].second,value);
            emit dataChanged(index,index,{Qt::DisplayRole,Qt::EditRole});
        }
        return true;
    }
    return false;
 }

Qt::ItemFlags TableDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}


bool TableDataModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row = 0 ; row<rows;row++){
        delete m_dataList[position];
        m_dataList.removeAt(position);
    }
    endRemoveRows();
    return true;
}


QList<TableAttributable*>& TableDataModel::get_data(){
    return m_dataList;
}

void TableDataModel::setDelegateForNestedAttributes(QTableView *table, QStyledItemDelegate *qd){
    for (int i = 0;i<headers.length(); i++){
        if (headers[i].first)
            table->setItemDelegateForColumn(i,qd);
    }
}
