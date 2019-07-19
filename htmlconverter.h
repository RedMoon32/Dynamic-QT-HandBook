#ifndef HTMLCONVERTER_H
#define HTMLCONVERTER_H

#include "basetableclass.h"

#define DEFAULT_TEMPLATE_PATH "./template.html"


class HtmlConverter
{
private:
    QString getTableRows(const QList<QPair<bool, const char*>>& props, QList<TableAttributable*>& table);
    QString getNestedRow(TableAttributable* t, const char *itemName);
    QString createHtmlTag(QString tagName, QString childrenElements, QString tagattributes ="");

    QString m_template;
public:
    HtmlConverter(QString templatePath = DEFAULT_TEMPLATE_PATH);
    QString convertToHtml(QList<TableAttributable*> &table);
};

#endif // HTMLCONVERTER_H
