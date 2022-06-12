//
// Created by 黎明余光 on 2022/6/10.
//

#ifndef CPP_TERM_PROJECT_RECORDSMODEL_H
#define CPP_TERM_PROJECT_RECORDSMODEL_H

#include <QAbstractTableModel>
#include "db/User.h"
#include "db/Record.h"

class RecordsModel : public QAbstractTableModel {
Q_OBJECT

public:
    RecordsModel(QObject *parent = nullptr);
//    RecordsModel(std::vector<User> users, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
//    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
//    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
//    const std::vector<User> &getUsers() const;
//    void setUsers(std::vector<User> users);

public slots:

    void fetchData();

    void fetchDataByAccountId(int accountId);
    void fetchDepositsByAccountId(int accountId);

    void fetchDataByUserId(int userId);

private:
    std::vector<Record> records;
};


#endif //CPP_TERM_PROJECT_RECORDSMODEL_H
