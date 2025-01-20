#include "jobtitle.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void JobTitleModel::loadData() {
    beginResetModel();
    m_jobtitle.clear();

    QSqlQuery query ("SELECT * FROM jobtitle");
    while (query.next()){
        JobTitle jobtitle;
        jobtitle.id = query.value("id").toInt();
        jobtitle.name = query.value("name").toString();
        jobtitle.salary = query.value("salary").toInt();
        jobtitle.StandartHours = query.value("StandartHours").toInt();

        m_jobtitle.append(jobtitle);
    }
    endResetModel();
}

QVariant JobTitleModel::data(const QModelIndex &index, int role) const{
    qDebug()<<"INDEX"<<index;
    if (!index.isValid() || index.row() >= m_jobtitle.size())
        return QVariant();
    const  JobTitle &jobtitle = m_jobtitle.at(index.row());
    qDebug()<<jobtitle.id<<jobtitle.name<<"TEXT";
    switch(role){
    case JobTitleIdRole:
        return jobtitle.id;
    case NameRole:
        return jobtitle.name;

    case SalaryRole:
        return jobtitle.salary;
    case StandartHoursRole:
        return jobtitle.StandartHours;
    default:
        return QVariant();
    }
}
int JobTitleModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return m_jobtitle.count();
}

void JobTitleModel::addJobtitle(const QString &name, double salary, double StandartHours) {
    QSqlQuery query;
    query.prepare("INSERT INTO jobtitle (name, salary, StandartHours) VALUES (?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(salary);
    query.addBindValue(StandartHours);

    if (query.exec()) {
        loadData(); // обновляем модель после добавления
    } else {
        qWarning() << "Ошибка добавления компании:" << query.lastError();
    };

    JobTitle newjobtitle;
    newjobtitle.id = query.lastInsertId().toInt();
    newjobtitle.name = name;
    newjobtitle.salary = salary;
    newjobtitle.StandartHours = StandartHours;
    beginInsertRows(QModelIndex(), m_jobtitle.size(), m_jobtitle.size());
    m_jobtitle.append(newjobtitle);
    endInsertRows();
}

void JobTitleModel::updateJobtitle(const QString &name, int id, double salary, double StandartHours){
    QSqlQuery query;
    query.prepare("UPDATE jobtitle SET name = ?, salary = ?, StandartHours = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(salary);
    query.addBindValue(StandartHours);
    query.addBindValue(id);

    if (query.exec()) {
        loadData(); // обновляем модель после редактирования
    }
    else {
        qWarning() << "Ошибка обновления компании:" << query.lastError();
    }
    loadData();
}

void JobTitleModel::removeJobtitle(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM jobtitle WHERE id = ?");
    query.addBindValue(id);

    if (query.exec()) {
        loadData(); // обновляем модель после удаления
    } else {
        qWarning() << "Ошибка удаления компании:" << query.lastError();
    }
    loadData();
}

QHash<int, QByteArray> JobTitleModel::roleNames() const{
    QHash<int,QByteArray> roles;
    roles[JobTitleIdRole] = "jobtitleId";
    roles[NameRole] = "name";
    roles[SalaryRole] = "salary";
    roles[StandartHoursRole] = "StandartHours";
    return roles;
}
