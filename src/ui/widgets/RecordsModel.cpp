//
// Created by 黎明余光 on 2022/6/10.
//

#include "RecordsModel.h"
#include "db/Db.h"

#include <QtWidgets>

RecordsModel::RecordsModel(QObject *parent)
        : QAbstractTableModel(parent)
{
    fetchData();
}

//RecordsModel::RecordsModel(std::vector<User> users, QObject *parent)
//        : QAbstractTableModel(parent), users(users)
//{
//}

int RecordsModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : records.size();
}

int RecordsModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 7;
}

QVariant RecordsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= records.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &record = records.at(index.row());

        switch (index.column()) {
            case 0:
                return record.id;
            case 1:
                return QString::number((double) record.amount / 100, 'f', 2);
            case 2:
                if (record.from == -1) return QString("-");
                return QString::number(record.from);
            case 3:
                if (record.to == -1) return QString("-");
                return QString::number(record.to);
            case 4:
                return QString(RecordTypeToString(record.type).c_str());
            case 5:
                if (record.type != RecordType::FixedDeposit) {
                    return QString("-");
                } else {
                    auto msg = QString::number(record.interestRate, 'f', 2);
                    if (record.isRedeemed) {
                        msg.append(QString(" (Redeemed)"));
                    } else {
                        msg.append(QString(" (Active)"));
                    }
                    return msg;
                }
            case 6:
                return QString(record.time.c_str());
            default:
                break;
        }
    } else if (role == Qt::EditRole) {
        return records.at(index.row()).id;
    }
    return QVariant();
}

QVariant RecordsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("No.");
            case 1:
                return tr("Amount");
            case 2:
                return tr("From");
            case 3:
                return tr("To");
            case 4:
                return tr("Type");
            case 5:
                return tr("Interest Rate");
            case 6:
                return tr("Time");
            default:
                break;
        }
    }
    return QVariant();
}

//bool RecordsModel::insertRows(int position, int rows, const QModelIndex &index)
//{
//    Q_UNUSED(index);
//    beginInsertRows(QModelIndex(), position, position + rows - 1);
//
//    for (int row = 0; row < rows; ++row)
//        contacts.insert(position, { QString(), QString() });
//
//    endInsertRows();
//    return true;
//}
////! [4]
//
////! [5]
//bool RecordsModel::removeRows(int position, int rows, const QModelIndex &index)
//{
//    Q_UNUSED(index);
//    beginRemoveRows(QModelIndex(), position, position + rows - 1);
//
//    for (int row = 0; row < rows; ++row)
//        contacts.removeAt(position);
//
//    endRemoveRows();
//    return true;
//}
////! [5]
//
////! [6]
//bool RecordsModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (index.isValid() && role == Qt::EditRole) {
//        const int row = index.row();
//        auto contact = contacts.value(row);
//
//        switch (index.column()) {
//            case 0:
//                contact.name = value.toString();
//                break;
//            case 1:
//                contact.address = value.toString();
//                break;
//            default:
//                return false;
//        }
//        contacts.replace(row, contact);
//        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
//
//        return true;
//    }
//
//    return false;
//}

Qt::ItemFlags RecordsModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if (index.column() != 0) {
        // TODO: flags
//        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
        return QAbstractTableModel::flags(index);
    } else {
        return QAbstractTableModel::flags(index);
    }
}

//const std::vector<User> &RecordsModel::getUsers() const {
//    return users;
//}

//void RecordsModel::setUsers(std::vector<User> tusers) {
//    users = tusers;
//}

void RecordsModel::fetchData() {
    records = Db::getStorage().get_all<Record>();
}

void RecordsModel::fetchDataByAccountId(int accountId) {
    records = Db::getStorage().get_all<Record>(where(c(&Record::from) == accountId or c(&Record::to) == accountId));
}

void RecordsModel::fetchDataByUserId(int userId) {
    auto accounts = Db::getStorage().get_all<Account>(where(c(&Account::belong_to) == userId));
    for (auto account : accounts) {
        auto temp = Db::getStorage().get_all<Record>(where(c(&Record::from) == account.id or c(&Record::to) == account.id));
        records.insert(records.end(), temp.begin(), temp.end());
    }
}
