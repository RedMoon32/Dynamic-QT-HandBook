#ifndef HTMLCONVERTER_H
#define HTMLCONVERTER_H

#include "basetableclass.h"



class HtmlConverter
{
public:
    static QString convertToHtml(QList<TableAttributable*> &table);
    static QString getElements(const QList<QPair<bool, const char*>>& props, QList<TableAttributable*>& table);
};

#endif // HTMLCONVERTER_H
