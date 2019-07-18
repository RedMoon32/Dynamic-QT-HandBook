#ifndef TABLEDATAMODEL_H
#define TABLEDATAMODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QTableView>
#include "entity.h"

class TableDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableDataModel(QList<TableAttributable*> &dataLst, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole)  Q_DECL_OVERRIDE;
    template<typename T> bool insertRows(int position, int rows, const QModelIndex &index);
    bool removeRows(int position, int rows, const QModelIndex &parent) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QList<TableAttributable*>& getData();
    void setDelegateForNestedAttributes(QTableView *table, QStyledItemDelegate* qd);
private:
    QList<TableAttributable*>& m_dataList;
    QList<QPair<bool,const char *>> headers;
};

template<typename T> bool TableDataModel::insertRows(int position, int rows, const QModelIndex &index){
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows-1);
    for (int row = 0; row < rows; ++row){
        m_dataList.append(new T());
    }
    endInsertRows();
    return true;
}

#endif // TABLEDATAMODEL_H
