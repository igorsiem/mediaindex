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

#ifndef _gui_mainwindow_h_installed
#define _gui_mainwindow_h_installed

#include <QMainWindow>
#include <QSettings>

/**
 * Qt framework generated user interface classes
 */
namespace Ui {
    class MainWindow;   ///< The Qt-generated version of the MainWindow class
}

/**
 * \brief The main window of the application
 * 
 * For clarity and general code-tidyness, the implementation of this class
 * has been broken up across several `.cpp` files. Apart from the
 * `mainwindow.cpp`, the rest of these are found in the `src/mainwindow`
 * folder.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    // --- External Interface ---

    public:

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

    // --- Internal Declarations ---

    protected:

    // -- Event Management --

    /**
     * \brief Handle shut-down actions, incuding writing window state and
     * geometry to persistent storage
     * 
     * \param event The event object (passed to base-class implementation) 
     */
    virtual void closeEvent(QCloseEvent *event) override;

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

};  // end MainWindow class

#endif
