#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>

struct Employee{
    int id;
    QString name;
    int id_company;
    int id_jobtitle;
    QString email;
    QString phone;
};

class EmployeeModel : public QSqlQueryModel {
    Q_OBJECT
public:
    enum EmployeeRoles{
        EmployeeIdRole = Qt::UserRole + 1,
        NameRole,
        id_CompanyRole,
        id_JobTitleRole,
        EmailRole,
        PhoneRole,
    };
    explicit EmployeeModel(QObject *parent = nullptr) : QSqlQueryModel(parent) {
        loadData();
    }


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE void loadData();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    // Структура данных для QML
    QString employeeId(int index) const {
        return QSqlQueryModel::data(QSqlQueryModel::index(index, 0)).toString();
    }

public slots:
    Q_INVOKABLE void addEmployee(const QString &name, int id_company,int id_jobtitle, QString email, QString phone);

    Q_INVOKABLE void updateEmployee(const QString &name, int id, int id_company, int id_jobtitle, QString email, QString phone);

    Q_INVOKABLE void removeEmployee(int id);
private:
    QList<Employee> m_employee;
};


#endif // EMPLOYEE_H
