#include "basetableclass.h"

/**
  Base Class for all data models from table
  */

QList<QString> ignore_list = {"Id","objectName"};

/**
 * Public constructor just to create an object and then
 * changing it's properties using QMeta
 */
TableAttributable::TableAttributable(){}

/**
 * @brief Return string value of attribute by name, if value is
 * other TableAttributble* then return value's primary attribute
 * @param name - name of attribute
 * @return value
 */
QString TableAttributable::getAttribute(const char* name){
    QVariant value = this->property(name);
    if (value.type()!= QVariant::UserType && value.canConvert(QMetaType::QString))
        return value.toString();
    else if (value.canConvert<TableAttributable*>()){
        TableAttributable* nested_table = qvariant_cast<TableAttributable*>(value);
        if (nested_table!=nullptr)
            return nested_table->getPrimaryAttribute();
    }
    return "";
}

/**
 * @brief Return primary attribute's value - in our case
 * properties'value with 'name' in property title
 *
 * @return stringed value
 */
QString TableAttributable::getPrimaryAttribute(){
    for (QString pr_name:this->getAttributeNames()){
        if (pr_name.contains(VISIBLE_COLUMN,Qt::CaseInsensitive)){
            return this->property(pr_name.toLocal8Bit().data()).toString();
        }
    }
    return "";
}

/**
 * @brief Get names of properties
 *
 * @return QList of available to display properties
 */
QList<const char*> TableAttributable::getAttributeNames(){
    QList<const char*> names;
    for (auto pair:getAttributeProperties()){
        names.append(pair.second);
    }
    return names;
}

/**
 * @brief Return List of pairs which contains info
 * about properties able to display - which are able to convert
 * to QString or which by self are TableAttributble*
 * @return QList<bool,string> , bool defines where it is TableAttributable*,
 * string defines name of property
 */
QList<QPair<bool,const char *>> TableAttributable::getAttributeProperties(){
    const QMetaObject *metaobject = this->metaObject();
    int count = metaobject->propertyCount();
    QList<QPair<bool,const char *>> res;
    for (int i = 0; i < count; ++i){
        QMetaProperty metaproperty = metaobject->property(i);
        auto name = metaproperty.name();
        if (!ignore_list.contains(name)){
            bool nested_attribute = false;
            auto value = this->property(name);
            if (value.canConvert<TableAttributable*>())
                nested_attribute = true;
            res.append(QPair<bool, const char*>(nested_attribute,name));
        }
    }
    return res;
}

