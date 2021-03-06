/**
 * \file mainwindow.h
 * Declare the main window class
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <QFileSystemModel>
#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QSettings>
#include <QSplitter>
#include <QTreeView>

#include "error.h"
#include "iconproxymodel.h"

#ifndef _gui_mainwindow_h_installed
#define _gui_mainwindow_h_installed

/**
 * Qt framework generated user interface classes
 */
namespace Ui {
    class MainWindow;   ///< The Qt-generated version of the MainWindow class
}

/**
 * \brief The main window of the application
 * 
 * \par Setup
 * As with most Qt widgets, GUI setup is invoked from the constructor. This
 * calls two major methods:
 * 
 * * `setupUi` -- instantiates the various widget objects
 * 
 * * `setupActions` -- sets up the action objects along with the menu and
 *   toolbar
 * 
 * Where possible, UI widgets are created anonymously, relying on the Qt
 * object hierarchy to manage deletion safely. Only widget objects that need
 * to be referenced after creation are retained as pointer attributes of the
 * `MainWindow` object.
 * 
 * The `MainWindow` constructor also performs some internal signal / slot
 * connections after the initial setup.
 * 
 * \par Conventions
 * Within the `MainWindow` class, several coding conventions are observed for
 * consistency:
 * 
 * * Slots are treated very much like event handlers, and slot method names
 *   are prefixed with the word "handle"
 * 
 * * In the hierarchy of setup methods, the prefix "setup" is used for
 *   methods that instantiate widget pointer attributes, but `create` is
 *   used to prefix methods that return a pointer to a newly created object
 *   that will be inserted into the object hierarchy, but *not* retained as
 *   an attribute
 * 
 * * The word "execute" is used to prefix the names of methods that implement
 *   Actions. The general approach is to instantiate a `QAction` object for
 *   every entry in the menu or toolbar, and then connect this with a C++
 *   lamda function that invokes the `execute*` methods
 * 
 * \par Implementation Files
 * This class is rather large. For clarity and general code-tidyness, method
 * implementations of this class have been broken up across several `.cpp`
 * files. Apart from the `mainwindow.cpp`, the rest of these are found in the
 * `src/gui/mainwindow` folder.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    // --- External Interface ---

    public:

    /**
     * \brief Error exception for signalling errors related to this class
     * 
     * See the \ref error_handling page for more info about error-handling
     * in *MediaIndex*.
     */
    class Error : public ::Error
    {
        public:

        /**
         * \brief Constructor, setting the exception object with a QString
         * 
         * \param msg The human-readable error message
         */
        explicit Error(QString msg) : ::Error(msg) {}

        DECLARE_DEFAULT_VIRTUAL_DESTRUCTOR(Error)

        /**
         * \brief Throw the error object as an exception
         */
        virtual void raise(void) const override { throw *this; }

        /**
         * \`brief Create a cloned copy of the Error object
         * 
         * \return A pointer to a new copy of self, created using `new`
         */
        virtual Error* clone(void) const override
            { return new Error(*this); }

    };  // end Error class

    /**
     * \brief Trivial constructor
     * 
     * This method sets up all user interface elements for the window.
     * 
     * \param settings A Qt settings object, for storing persistent
     * configuration data (e.g. window geometry)
     * 
     * \param parent The parent UI object (usually `nullptr`)
     */
    explicit MainWindow(QSettings& settings, QWidget *parent = nullptr);

    /**
     * \brief Destructor - destroys all user interface elements for this
     * window
     */
    ~MainWindow();

    signals:

    /**
     * \brief Notify that the root folder has been changed
     * 
     * \param newRootDirectory The path to the new root directory
     */
    void rootDirectoryChanged(QString newRootDirectory);

    /**
     * \brief Notify that the directory selected for viewing has changed
     * 
     * \param newSelectedDirectory The new folder selection
     */
    void selectedDirectoryChanged(QString newSelectedDirectory);

    /**
     * \brief Signal that a file has been selected for viewing
     * 
     * \param selectedFilePath The path of the selected file
     */
    void fileSelected(QString selectedFilePath);

    // --- Internal Declarations ---

    protected:

    // -- Event Handling --
    //
    // These methods are implemented in `mainwindow/mw_events.cpp`. Note
    // that this includes Qt slot methods as well.

    /**
     * \brief Handle shut-down actions, incuding writing window state and
     * geometry to persistent storage
     * 
     * \param event The event object (passed to base-class implementation) 
     */
    virtual void closeEvent(QCloseEvent *event) override;

    protected slots:

    /**
     * \brief Perform all necessary actions when the root folder has
     * changed
     * 
     * This includes updating the folder tree / model objects.
     * 
     * \param newRootDirectory The path of the directory that was selected
     * as the root
     */
    void handleRootDirectoryChanged(QString newRootDirectory);

    /**
     * \brief Perform display and update actions in response to the selected
     * directory changing
     * 
     * \param newSelectedDirectory The path of the directory that was
     * selected
     */
    void handleSelectedDirectoryChanged(QString newSelectedDirectory);

    /**
     * \brief Perform display and update actions in response to a file
     * being selected
     * 
     * \param filePath The path of the selected file
     */
    void handleFileSelected(QString filePath);

    private:

    // -- UI Setup --
    //
    // These methods are implemented in the `mainwindow/mw_setup_ui.cpp`
    // file.
    
    /**
     * \brief Top-level method for setting up the UI
     * 
     * This method is called once from the constructor. All other UI setup /
     * creation methods are called from here.
     */
    void setupUi(void);

    /**
     * \brief Set up the central widget and all its components
     * 
     * This method is called once during construction.
     */
    void setupCentralWidget(void);

    /**
     * \brief Create the main left/right splitter and its components
     * 
     * This method is called once during construction.
     * 
     * \return The newly created `QSplitter` object, ready to be inserted
     * into its parent; note there is no need to reference this object after
     * it is created, so it is not retained as an attribute of the
     * `MainWindow`.
     */
    QSplitter* createLeftRightSplitter(void);

    /**
     * \brief Set up the `m_folderTrVw` and `m_folderMdl` objects that manage
     * the folder tree view
     * 
     * This method is called once during construction.
     */
    void setupFolderTreeView(void);

    /**
     * \brief Create the vertical splitter between the Files List View and
     * the Image Display Label
     * 
     * \return A pointer to the splitter object; note that this is not
     * retained as an attribute of the `MainWindow` object because it is
     * not referenced after construction
     */
    QSplitter* createTopBottomSplitter(void);

    /**
     * \brief Set up the `m_filesLstVw` and `m_filesMdl` objects that manage
     * the files displayed for the currently selected folder
     * 
     * This method is called once during construction.
     */
    void setupFileListView(void);

    // -- Actions Setup --
    //
    // These methods are implemented in the 'mainwindow/mw_setup_actions.cpp`
    // file.

    /**
     * \brief Set up the User command actions, and their corresponding
     * menu items and toolbar buttons
     * 
     * This method is called once during construction
     */
    void setupActions(void);

    /**
     * \brief Set up the User command actions related to File operations
     * 
     * This method is called once during constructions
     */
    void setupFileActions(void);

    // -- Command Execution --

    /**
     * \brief Execute the User action to open / set the root folder for
     * browsing
     */
    void executeFileOpenRootFolderAction(void);

    // -- Utilities / Helper Methods --
    //
    // The methods below are implemented in the `mainwindow/mw_utils.cpp`
    // file.

    /**
     * \brief Save the current window geometry to persistent settings
     */
    void saveWindowGeometry(void);

    /**
     * \brief Retrieve window geometry from persistent settings
     */
    void restoreWindowGeometry(void);

    /**
     * \brief Retrieve the path of the root folder for the index
     * 
     * This is retrieved from persistent user settings. If it has not been
     * set, the default pictures folder path.
     * 
     * \param The path to the root directory for the index
     */
    QString rootDirectoryPath(void) const;

    /**
     * \brief Record the root directory path for the index in persistent
     * settings storage
     * 
     * Note that this method does not update the UI.
     * 
     * \param p The path to set
     */
    void saveRootDirectoryPath(QString p);

    /**
     * \brief Retrieve the path of the most recently selected directory from
     * persistent storage
     */
    QString selectedDirectoryPath(void) const;

    /**
     * \brief Save the path of the most recently selected directory from
     * persistent storage
     */
    void saveSelectedDirectoryPath(QString p);

    /**
     * \brief Display the file referenced by `m_displayedFilePath`, scaled
     * to the display label
     * 
     * \todo Expand this functionality for other file types
     */
    void redisplayFile(void);

    // -- Attributes --

    /**
     * \brief Qt-generated framework for the main window
     */
    Ui::MainWindow *ui;

    /**
     * \brief A reference to the application-wide setings object that is used
     * for persistent settings information
     */
    QSettings& m_settings;

    // - User Interface Elements -

    QTreeView* m_foldersTrVw;       ///< The tree view for folders
    QFileSystemModel* m_foldersMdl; ///< The data model for folders
    QListView* m_filesLstVw;        ///< List view for media files
    QFileSystemModel* m_realFilesMdl;   ///< Data model for media files
    IconProxyModel* m_filesMdl;     ///< Proxy for generating icons for files
    QLabel* m_imageLbl;             ///< Label for displaying selected image
    QString m_displayedFilePath;    ///< Path of currently displayed file

};  // end MainWindow class

#endif
