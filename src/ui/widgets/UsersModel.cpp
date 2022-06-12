//
// Created by 黎明余光 on 2022/6/10.
//

#include "UsersModel.h"
#include "db/Db.h"

#include <QtWidgets>

UsersModel::UsersModel(QObject *parent)
        : QAbstractTableModel(parent)
{
    fetchData();
}

UsersModel::UsersModel(std::vector<User> users, QObject *parent)
        : QAbstractTableModel(parent), users(users)
{
}

int UsersModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : users.size();
}

int UsersModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 4;
}

QVariant UsersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= users.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &user = users.at(index.row());

        switch (index.column()) {
            case 0:
                return user.id;
            case 1:
                return QString(user.name.c_str());
            case 2:
                return QString(user.idNumber.c_str());
            case 3:
                return QString(user.phoneNumber.c_str());
            default:
                break;
        }
    } else if (role == Qt::EditRole) {
        return users.at(index.row()).id;
    }
    return QVariant();
}

QVariant UsersModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("No.");
            case 1:
                return tr("Name");
            case 2:
                return tr("ID Card Number");
            case 3:
                return tr("Phone Number");
            default:
                break;
        }
    }
    return QVariant();
}

//bool UsersModel::insertRows(int position, int rows, const QModelIndex &index)
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
//bool UsersModel::removeRows(int position, int rows, const QModelIndex &index)
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
//bool UsersModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

Qt::ItemFlags UsersModel::flags(const QModelIndex &index) const {
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

//const std::vector<User> &UsersModel::getUsers() const {
//    return users;
//}

void UsersModel::setUsers(std::vector<User> tusers) {
    users = tusers;
}

void UsersModel::fetchData() {
    users = Db::getStorage().get_all<User>(where(c(&User::employeeId) == -1));
}
