#include "htmlconverter.h"

QString HtmlConverter::convertToHtml(QList<TableAttributable*>& table)
{
    QString res;
    res+="<table><tr>";
    if (table.length()>0){
        auto props = table[0]->getAttributeProperties();
        for (int i = 0 ; i < props.length(); i++){
            if (!props[i].first){
                res+=QString("<th>%1</th>").arg(props[i].second);
            }
        }
        res+="</tr>";
        res+=getElements(props,table);
    }
    res+="</table>";
    return res;
}

QString HtmlConverter::getElements(const QList<QPair<bool, const char*>>& props, QList<TableAttributable*>& table){
    QString tr = "";
    for (auto const &item:table){
        QString hoverText = "";
        tr+= "<tr div title=\"%1\">";
        for (auto const &prop: props){
            if (!prop.first){
                tr+=QString("<td>%1</td>").arg(item->get_attribute(prop.second));
            }
            else{
                //hoverText+=QString()
            }
        }
        tr+="</tr>";
    }
    return tr;
}
