#ifndef IT_COMPANY_H
#define IT_COMPANY_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>

struct Company{
    int id;
    QString name;
    int expenses;
};

class IT_CompanyModel : public QSqlQueryModel {
    Q_OBJECT
public:
    enum CompanyRoles{
        CompanyIdRole = Qt::UserRole + 1,
        NameRole,
        ExpensesRole
    };
    explicit IT_CompanyModel(QObject *parent = nullptr) : QSqlQueryModel(parent) {
        loadData();
    }


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE void loadData();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    // Структура данных для QML
    QString companyId(int index) const {
        return QSqlQueryModel::data(QSqlQueryModel::index(index, 0)).toString();
    }

    QString name(int index) const {
        return QSqlQueryModel::data(QSqlQueryModel::index(index, 1)).toString();
    }

    double expenses(int index) const {
        return QSqlQueryModel::data(QSqlQueryModel::index(index, 2)).toDouble();
    }
public slots:
    Q_INVOKABLE void addCompany(const QString &name, double expenses);

    Q_INVOKABLE void updateCompany(const QString &name, int id, double expenses);

    Q_INVOKABLE void removeCompany(int id);
private:
    QList<Company> m_company;
};

#endif // IT_COMPANY_H
