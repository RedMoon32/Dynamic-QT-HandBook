#ifndef DYNAMICLISTATTRIBUTBLE_H
#define DYNAMICLISTATTRIBUTBLE_H

#include <QObject>
#include <QMetaProperty>
#include <QDebug>
#include <QMetaObject>

QList<QString> ignore_list = {"objectName", "Id"};

class TableAttributable: public QObject{
    Q_OBJECT
public:
    QList<QPair<QString, QString>> get_attributes(){
        const QMetaObject *metaobject = this->metaObject();
        int count = metaobject->propertyCount();
        QList<QPair<QString, QString>> res;
        for (int i = 0; i < count; ++i){
            QMetaProperty metaproperty = metaobject->property(i);
            const char *name = metaproperty.name();
            const QVariant& value = this->property(name);
            qInfo() << name;
            if (value.userType() == QMetaType::QString && !ignore_list.contains(name))
                res.append(qMakePair(name, value.toString()));
            else{
                 TableAttributable *nested_table = value.value<TableAttributable*>();
                 if (nested_table!=nullptr)
                    res.append(nested_table->get_attributes());
            }
        }
        return res;
    }
};


#endif // DYNAMICLISTATTRIBUTBLE_H
