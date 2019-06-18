/**
 * \file iconproxymodel.h
 * Declare the `IconProxyModel` class
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <QIcon>
#include <QIdentityProxyModel>
#include <QMap>
#include <QPersistentModelIndex>
#include <QtConcurrent>

#ifndef _gui_iconproxymodel_h_installed
#define _gui_iconproxymodel_h_installed

/**
 * \brief A proxy model for making display icons from image files
 * 
 * This proxy model substitutes an image icon (from an image file) when data
 * for the `QFileSystemModel::FileIconRole` is requested for a given file.
 * When an icon is requested for a given file path, an internal icon map is
 * checked to see if an icon for that file has already been created. If so,
 * it is simply returned.
 * 
 * If not, a `QtConcurrent` background task is invoked to load the image and
 * make it into an icon. When this completes, the new icon is added to the
 * internal store ad the standard `dataChanged` signal is emitted.k
 */
class IconProxyModel : public QIdentityProxyModel
{

    Q_OBJECT

    public:

    /**
     * \brief Standard constructor for Qt classes / objects
     * 
     * \param parent The parent of the object
     */
    explicit IconProxyModel(QObject* parent = nullptr);

    /**
     * \brief Retrieve data for a given item and role in the model
     * 
     * This method is overridden so that file icons are retrieved when the
     * role is `QFileSystemModel::FileIconRole`
     * 
     * \param index The index of the data item
     * 
     * \param role The display / view role for which the data being requested
     */
    virtual QVariant data(
            const QModelIndex & index
            , int role) const override;

    /**
     * \brief Clear the internal icon map
     * 
     * This can be called to prevent the internal icon store getting too big.
     */
    void clearIconMap(void) { m_iconMap.clear(); }

    signals:

    /**
     * Signal that an icon image has been loaded
     * 
     * \param p The path of the file for the icon
     * 
     * \param i The icon object
     * 
     * \param idx The index object for the fule
     */
    void hasIcon(
        const QString& p
        , const QIcon& i
        , const QPersistentModelIndex& idx) const;

    protected slots:

    /**
     * \brief Store a loaded icon and emit the `dataChanged` signal so that
     * any views for this model are updated
     * 
     * This method is invoked after an icon has been loaded in a background
     * thread.
     * 
     * \param path The path of the file from which the icon has been
     * generated
     * 
     * \param icon The icon object
     * 
     * \param index The index object for the file in the model
     */
    void onIcon(
        const QString& path
        , const QIcon& icon
        , const QPersistentModelIndex& index);

    protected:

    /**
     * The internal store of created icons
     */
    QMap<QString, QIcon> m_iconMap;

};  //end IconProxyModel

#endif
