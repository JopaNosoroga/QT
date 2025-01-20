#include "projects.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void ProjectModel::loadData() {
    beginResetModel();
    m_project.clear();

    QSqlQuery query ("SELECT * FROM projects");
    while (query.next()){
        Project project;
        project.id = query.value("id").toInt();
        project.name = query.value("name").toString();
        project.id_company = query.value("id_company").toInt();

        m_project.append(project);
    }
    endResetModel();
}

QVariant ProjectModel::data(const QModelIndex &index, int role) const{
    qDebug()<<"INDEX"<<index;
    if (!index.isValid() || index.row() >= m_project.size())
        return QVariant();
    const  Project &project = m_project.at(index.row());
    switch(role){
    case ProjectIdRole:
        return project.id;
    case NameRole:
        return project.name;

    case id_CompanyRole:
        return project.id_company;
    default:
        return QVariant();
    }
}
int ProjectModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return m_project.count();
}

void ProjectModel::addProject(const QString &name, int id_company) {
    QSqlQuery query;
    query.prepare("INSERT INTO projects (name, id_company) VALUES (?, ?)");
    query.addBindValue(name);
    query.addBindValue(id_company);

    if (query.exec()) {
        loadData(); // обновляем модель после добавления
    } else {
        qWarning() << "Ошибка добавления компании:" << query.lastError();
    };

    Project newproject;
    newproject.id = query.lastInsertId().toInt();
    newproject.name = name;
    newproject.id_company = id_company;
    beginInsertRows(QModelIndex(), m_project.size(), m_project.size());
    m_project.append(newproject);
    endInsertRows();
}

void ProjectModel::updateProject(const QString &name, int id, int  id_company){
    QSqlQuery query;
    query.prepare("UPDATE projects SET name = ?, id_company = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(id_company);
    query.addBindValue(id);

    if (query.exec()) {
        loadData(); // обновляем модель после редактирования
    }
    else {
        qWarning() << "Ошибка обновления компании:" << query.lastError();
    }
    loadData();
}

void ProjectModel::removeProject(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM projects WHERE id = ?");
    query.addBindValue(id);

    if (query.exec()) {
        loadData(); // обновляем модель после удаления
    } else {
        qWarning() << "Ошибка удаления компании:" << query.lastError();
    }
    loadData();
}

QHash<int, QByteArray> ProjectModel::roleNames() const{
    QHash<int,QByteArray> roles;
    roles[ProjectIdRole] = "companyId";
    roles[NameRole] = "name";
    roles[id_CompanyRole] = "id_company";
    return roles;
}
