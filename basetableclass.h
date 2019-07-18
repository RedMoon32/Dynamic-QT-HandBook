#ifndef BASETABLECLASS_H
#define BASETABLECLASS_H

#include <QObject>
#include <QMetaProperty>
#include <QDebug>

#define VISIBLE_COLUMN "name"
extern QList<QString> ignore_list;

class TableAttributable: public QObject{
    Q_OBJECT
public:
    TableAttributable();
    QString get_attribute(const char* name);
    QList<QPair<bool,const char *>> getAttributeProperties();
    QList<const char *> getNestedAttributes();
    QList<const char*> getAttributeNames();
    QString getPrimaryAttributes();
};

#endif // BASETABLECLASS_H
