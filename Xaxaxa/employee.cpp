#include "employee.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void EmployeeModel::loadData() {
    beginResetModel();
    m_employee.clear();

    QSqlQuery query ("SELECT * FROM employee");
    while (query.next()){
        Employee employee;
        employee.id = query.value("id").toInt();
        employee.name = query.value("name").toString();
        employee.id_company = query.value("id_company").toInt();
        employee.id_jobtitle = query.value("id_jobtitle").toInt();
        employee.email = query.value("email").toString();
        employee.phone = query.value("phone").toString();
        m_employee.append(employee);
    }
    endResetModel();
}

QVariant EmployeeModel::data(const QModelIndex &index, int role) const{
    qDebug()<<"INDEX"<<index;
    if (!index.isValid() || index.row() >= m_employee.size())
        return QVariant();
    const  Employee &employee = m_employee.at(index.row());
    switch(role){
    case EmployeeIdRole:
        return employee.id;
    case NameRole:
        return employee.name;

    case id_CompanyRole:
        return employee.id_company;
    case id_JobTitleRole:
        return employee.id_jobtitle;
    case EmailRole:
        return employee.email;
    case PhoneRole:
        return employee.phone;
    default:
        return QVariant();
    }
}
int EmployeeModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return m_employee.count();
}

void EmployeeModel::addEmployee(const QString &name, int id_company, int id_jobtitle, QString email, QString phone) {
    QSqlQuery query;
    query.prepare("INSERT INTO employee (name, id_company, id_jobtitle, email, phone) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(id_company);
    query.addBindValue(id_jobtitle);
    query.addBindValue(email);
    query.addBindValue(email);
    query.addBindValue(phone);

    if (query.exec()) {
        loadData(); // обновляем модель после добавления
    } else {
        qWarning() << "Ошибка добавления компании:" << query.lastError();
    };

    Employee newemployee;
    newemployee.id = query.lastInsertId().toInt();
    newemployee.name = name;
    newemployee.id_company = id_company;
    beginInsertRows(QModelIndex(), m_employee.size(), m_employee.size());
    m_employee.append(newemployee);
    endInsertRows();
}

void EmployeeModel::updateEmployee(const QString &name, int id, int id_company,int id_jobtitle, QString email, QString phone ){
    QSqlQuery query;
    query.prepare("UPDATE employee SET name = ?, id_company = ?, id_jobtitle = ?, email = ?, phone = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(id_company);
    query.addBindValue(id_jobtitle);
    query.addBindValue(email);
    query.addBindValue(phone);
    query.addBindValue(id);

    if (query.exec()) {
        loadData(); // обновляем модель после редактирования
    }
    else {
        qWarning() << "Ошибка обновления компании:" << query.lastError();
    }
    loadData();
}

void EmployeeModel::removeEmployee(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM employee WHERE id = ?");
    query.addBindValue(id);

    if (query.exec()) {
        loadData(); // обновляем модель после удаления
    } else {
        qWarning() << "Ошибка удаления компании:" << query.lastError();
    }
    loadData();
}

QHash<int, QByteArray> EmployeeModel::roleNames() const{
    QHash<int,QByteArray> roles;
    roles[EmployeeIdRole] = "employeeId";
    roles[NameRole] = "name";
    roles[id_CompanyRole] = "id_company";
    roles[id_JobTitleRole] = "id_jobtitle";
    roles[EmailRole] = "email";
    roles[PhoneRole] = "phone";
    return roles;
}

