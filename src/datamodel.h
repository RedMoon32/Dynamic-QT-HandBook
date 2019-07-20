#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QMetaProperty>
#include "entity.h"
#define DYNAMIC_LIST_POSTFIX "_List"

class DataModel : public QObject
{
    Q_OBJECT
    // упарываемся по полной
    Q_PROPERTY(const QList<Company*>& Company_List READ  getCompanyList)
    Q_PROPERTY(const QList<Country*>& Country_List READ  getCountryList)
    // add here your list if you want to display it
public:
    DataModel() {}

    void InitModel(){
        Country *NewCountry;

        NewCountry = new Country(QUuid::createUuid(), "United Arab Emirates");
        m_CountryList.append(NewCountry);
        m_CompanyList.append(new Company( QUuid::createUuid(), "ADCO", NewCountry,"Vasya" ));

        NewCountry = new Country(QUuid::createUuid(), "Italy");
        m_CountryList.append(NewCountry);
        m_CompanyList.append(new Company( QUuid::createUuid(), "Agip KCO", NewCountry, "Petya" ));

        NewCountry = new Country(QUuid::createUuid(), "Canada");
        m_CountryList.append(NewCountry);

        m_CompanyList.append(new Company( QUuid::createUuid(), "Cenovus Energy", NewCountry, "Vasya" ));

        NewCountry = new Country(QUuid::createUuid(), "Russia");
        m_CountryList.append(NewCountry);
    }

    ~DataModel() {
        qDeleteAll(m_CompanyList.begin(),m_CompanyList.end());
        qDeleteAll(m_CountryList.begin(),m_CountryList.end());
    }

    const QList<Company*> &getCompanyList() const{
        return m_CompanyList;
    }

    const QList<Country*> &getCountryList() const{
        return m_CountryList;
    }


    QList<Company*> &getCompanyList(){
        return m_CompanyList;
    }

    QList<Country*> &getCountryList(){
        return m_CountryList;
    }

private:
    QList<Company*> m_CompanyList;
    QList<Country*> m_CountryList;
};

#endif


