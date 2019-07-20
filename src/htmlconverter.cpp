#include "htmlconverter.h"

#include <QFile>
#include <QDir>

/**
 * @brief convert List of TableAttributable* to html-string
 * @param filePath - template to be used
 */
HtmlConverter::HtmlConverter(QString filePath){
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    QTextStream in(&file);
    m_template = in.readAll();
}

QString HtmlConverter::createHtmlTag(QString tagName, QString childrenElements, QString tagattributes){
    QString res = "<%1 %2>%3</%1>\n";
    return res.arg(tagName).arg(tagattributes).arg(childrenElements);
}

QString HtmlConverter::convertToHtml(QList<TableAttributable*>& table)
{
    QString res, ths;
    if (table.length()>0){
        auto props = table[0]->getAttributeProperties();
        for (int i = 0 ; i < props.length(); i++){
            if (!props[i].first){
                ths+=createHtmlTag("th",props[i].second);
            }
        }
        res = createHtmlTag("tr",ths);
        res += getTableRows(props,table);
    }
    res = createHtmlTag("table",res);
    return m_template.arg(res);
}

/**
 * @brief Get Info for popup window (e.g. Country Info)
 * @param item - pointer to nested item (e.g. Country*)
 * @param itemName - name of field in upper class (e.g. CompanyCountry)
 * @return string representing nested item
 */
QString HtmlConverter::getNestedRow(TableAttributable* item, const char *itemName){
    auto props = item->getAttributeProperties();
    QString res = QString(itemName)+" :\n\n";
    for (auto const&prop:props){
        if (!prop.first){
            res+=QString(prop.second)+" : "+item->property(prop.second).toString()+"\n";
        }
    }
    res+="\n";
    return res;
}

QString HtmlConverter::getTableRows(const QList<QPair<bool, const char*>>& props, QList<TableAttributable*>& table){
    QString tr;
    for (auto const &item:table){
        QString hoverText;
        QString td;
        for (auto const &prop: props){
            if (!prop.first){
                td+=createHtmlTag("td",item->getAttribute(prop.second));
            }
            else{
                auto nest = qvariant_cast<TableAttributable*>(item->property(prop.second));
                if (nest!=nullptr)
                    hoverText+=getNestedRow(nest,prop.second);
            }
        }
        if (hoverText == "")
            hoverText = "No additional infomation provided";
        td+=createHtmlTag("td", createHtmlTag("div",hoverText),"class='hidden'");
        tr+= createHtmlTag("tr", td);
    }
    return tr;
}
