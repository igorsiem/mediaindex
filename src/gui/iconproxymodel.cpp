/**
 * \file iconproxymodel.cpp
 * Implement the `IconProxyModel` class
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <QFileSystemModel>
#include <QPixmap>

#include "iconproxymodel.h"

IconProxyModel::IconProxyModel(QObject* parent) :
        QIdentityProxyModel(parent)
        , m_iconMap()
{
    connect(
        this
        , &IconProxyModel::hasIcon
        , this
        , &IconProxyModel::onIcon);
}

QVariant IconProxyModel::data(const QModelIndex & index, int role) const
{
    // Only substitute an Icon when a File Icon is requested
    if (role == QFileSystemModel::FileIconRole)
    {
        // Grab the path data, and if we already have an icon for this file
        // in our map, return that one.
        auto path = index.data(QFileSystemModel::FilePathRole).toString();
        auto it = m_iconMap.find(path);

        if (it != m_iconMap.end())
        {
            if (! it->isNull()) return *it;
            return QIdentityProxyModel::data(index, role);
        }
        else
        {
            // We don't have the icon in our map, so load it asynchronously.
            // For now, we return an empty variant. When the image icon has
            // been loaded, `hasIcon` will be emitted.
            QPersistentModelIndex pIndex{index};
            QtConcurrent::run([this,path,pIndex]{
                emit hasIcon(
                    path
                    , QIcon(QPixmap(path))
                    , pIndex);
            });

            return QVariant{};
        }
    }
    else return QIdentityProxyModel::data(index, role);
}   // end data method

void IconProxyModel::onIcon(
        const QString& path
        , const QIcon& icon
        , const QPersistentModelIndex& index)
    {
        m_iconMap.insert(path, icon);
        emit dataChanged(
            index
            , index
            , QVector<int>{QFileSystemModel::FileIconRole});
    }        
