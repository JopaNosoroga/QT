#ifndef JOBTITLE_H
#define JOBTITLE_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>

struct JobTitle{
    int id;
    QString name;
    int salary;
    int StandartHours;
};

class JobTitleModel: public QSqlQueryModel {
    Q_OBJECT
public:
    enum JobTitleRoles{
        JobTitleIdRole = Qt::UserRole + 1,
        NameRole,
        SalaryRole,
        StandartHoursRole
    };
    explicit JobTitleModel(QObject *parent = nullptr) : QSqlQueryModel(parent) {
        loadData();
    }


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE void loadData();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    // Структура данных для QML
    QString jobtitleId(int index) const {
        return QSqlQueryModel::data(QSqlQueryModel::index(index, 0)).toString();
    }

    QString name(int index) const {
        return QSqlQueryModel::data(QSqlQueryModel::index(index, 1)).toString();
    }

    double expenses(int index) const {
        return QSqlQueryModel::data(QSqlQueryModel::index(index, 2)).toDouble();
    }
public slots:
    Q_INVOKABLE void addJobtitle(const QString &name, double salary, double StandartHours);

    Q_INVOKABLE void updateJobtitle(const QString &name, int id, double salary, double StandartHours);

    Q_INVOKABLE void removeJobtitle(int id);
private:
    QList<JobTitle> m_jobtitle;
};


#endif // JOBTITLE_H
