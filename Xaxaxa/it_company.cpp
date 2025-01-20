#include "it_company.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void IT_CompanyModel::loadData() {
    beginResetModel();
    m_company.clear();

    QSqlQuery query ("SELECT * FROM companies");
    while (query.next()){
        Company company;
        company.id = query.value("id").toInt();
        company.name = query.value("name").toString();
        company.expenses = query.value("expenses").toInt();
        qDebug()<< company.name<< company.expenses<< company.id;

        m_company.append(company);
    }
    endResetModel();
}

QVariant IT_CompanyModel::data(const QModelIndex &index, int role) const{
    qDebug()<<"INDEX"<<index;
    if (!index.isValid() || index.row() >= m_company.size())
        return QVariant();
    const  Company &company = m_company.at(index.row());
    qDebug()<<company.id<<company.name<<"TEXT";
    switch(role){
    case CompanyIdRole:
        return company.id;
    case NameRole:
        return company.name;

    case ExpensesRole:
        return company.expenses;
    default:
        return QVariant();
    }
}
int IT_CompanyModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return m_company.count();
}

void IT_CompanyModel::addCompany(const QString &name, double expenses) {
    QSqlQuery query;
    query.prepare("INSERT INTO companies (name, expenses) VALUES (?, ?)");
    query.addBindValue(name);
    query.addBindValue(expenses);

    if (query.exec()) {
        loadData(); // обновляем модель после добавления
    } else {
        qWarning() << "Ошибка добавления компании:" << query.lastError();
    };

    Company newcompany;
    newcompany.id = query.lastInsertId().toInt();
    newcompany.name = name;
    newcompany.expenses = expenses;
    beginInsertRows(QModelIndex(), m_company.size(), m_company.size());
    m_company.append(newcompany);
    endInsertRows();
}

void IT_CompanyModel::updateCompany(const QString &name, int id, double expenses){
    QSqlQuery query;
    query.prepare("UPDATE companies SET name = ?, expenses = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(expenses);
    query.addBindValue(id);

    if (query.exec()) {
        loadData(); // обновляем модель после редактирования
    }
    else {
        qWarning() << "Ошибка обновления компании:" << query.lastError();
    }
    loadData();
}

void IT_CompanyModel::removeCompany(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM companies WHERE id = ?");
    query.addBindValue(id);

    if (query.exec()) {
        loadData(); // обновляем модель после удаления
    } else {
        qWarning() << "Ошибка удаления компании:" << query.lastError();
    }
    loadData();
}

QHash<int, QByteArray> IT_CompanyModel::roleNames() const{
    QHash<int,QByteArray> roles;
    roles[CompanyIdRole] = "companyId";
    roles[NameRole] = "name";
    roles[ExpensesRole] = "expenses";
    return roles;
}
