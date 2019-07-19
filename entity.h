#pragma once;

#include <QObject>
#include <QUuid>
#include <QMetaProperty>
#include "basetableclass.h"

class Country: public  TableAttributable
{
    Q_OBJECT
    Q_PROPERTY(QUuid Id READ getId WRITE setId)
    Q_PROPERTY(QString CountryName READ getCountryName WRITE setCountryName)
    Q_PROPERTY(int CountryPopulation READ getCountryPopulation WRITE setCountyPopulation)
public:
    explicit Country(QUuid Id, QString CountryName):
        m_Id{Id},
        m_CountryName{CountryName},
        m_CountryPopulation(10000)
    {}

     Country():
         m_Id(QUuid::createUuid()),
         m_CountryPopulation(10000),
         m_CountryName("New Country")
     {}
    ~Country(){}

    QUuid getId() const
    {
        return m_Id;
    }

    QString getCountryName() const
    {
        return m_CountryName;
    }

    int getCountryPopulation() const {
        return m_CountryPopulation;
    }


public slots:
    void setId(QUuid Id)
    {
        m_Id = Id;
    }

    void setCountryName(QString CountryName)
    {
        m_CountryName = CountryName;
    }

    void setCountyPopulation(int CountryPopulation){
        m_CountryPopulation = CountryPopulation;
    }

private:
    QUuid m_Id;
    QString m_CountryName;
    int m_CountryPopulation;
};

class Company: public TableAttributable
{
    Q_OBJECT
    Q_PROPERTY(QUuid Id READ getId WRITE setId)
    Q_PROPERTY(QString CompanyName READ getCompanyName WRITE setCompanyName)
    Q_PROPERTY(Country*CompanyCountry READ getCompanyCountry WRITE setCompanyCountry)
    Q_PROPERTY(QString Owner READ getOwner WRITE setOwner)
public:
    explicit Company(QUuid Id, QString CompanyName, Country *CompanyCountry, QString Owner):
        m_Id{Id},
        m_CompanyName{CompanyName},
        m_Owner(Owner),
        m_CompanyCountry{CompanyCountry}
    {}

    Company(): m_Id(QUuid::createUuid()), m_CompanyName("New Company"), m_CompanyCountry(nullptr){}

    ~Company()
    {}

    QUuid getId() const
    {
        return m_Id;
    }

    QString getCompanyName() const
    {
        return m_CompanyName;
    }

    Country *getCompanyCountry() const
    {
        return m_CompanyCountry;
    }

    QString getOwner() const{
        return m_Owner;
    }

    void setOwner(QString Owner)
    {
        m_Owner = Owner;
    }

public slots:
    void setId(QUuid Id)
    {
        m_Id = Id;
    }

    void setCompanyName(QString CompanyName)
    {
        m_CompanyName = CompanyName;
    }

    void setCompanyCountry(Country *CompanyCountry)
    {
        m_CompanyCountry = CompanyCountry;
    }

private:
    QUuid m_Id;
    QString m_CompanyName;
    QString m_Owner;
    Country *m_CompanyCountry;
};
