#include "basetableclass.h"

QList<QString> ignore_list = {"Id","objectName"};

TableAttributable::TableAttributable(){}

QString TableAttributable::get_attribute(const char* name){
    QVariant value = this->property(name);
    if (value.type()!= QVariant::UserType)
        return value.toString();
    else {
        TableAttributable* nested_table = qvariant_cast<TableAttributable*>(value);
        if (nested_table!=nullptr)
            return nested_table->getPrimaryAttributes();
    }
    return "";
}

QString TableAttributable::getPrimaryAttributes(){
    for (QString pr_name:this->getAttributeNames()){
        if (pr_name.contains(VISIBLE_COLUMN,Qt::CaseInsensitive)){
            return this->property(pr_name.toLocal8Bit().data()).toString();
        }
    }
    return "";
}

QList<const char*> TableAttributable::getAttributeNames(){
    QList<const char*> names;
    for (auto pair:getAttributeProperties()){
        names.append(pair.second);
    }
    return names;
}

QList<QPair<bool,const char *>> TableAttributable::getAttributeProperties(){
    const QMetaObject *metaobject = this->metaObject();
    int count = metaobject->propertyCount();
    QList<QPair<bool,const char *>> res;
    for (int i = 0; i < count; ++i){
        QMetaProperty metaproperty = metaobject->property(i);
        auto name = metaproperty.name();
        if (!ignore_list.contains(name)){
            bool nested_attribute = false;
            if (this->property(name).canConvert<TableAttributable*>())
                nested_attribute = true;
            res.append(QPair<bool, const char*>(nested_attribute,name));
        }
    }
    return res;
}

