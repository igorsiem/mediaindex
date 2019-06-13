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
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

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

    protected:

    /**
     * \brief Handle shut-down actions, incuding writing window state and
     * geometry to persistent storage
     * 
     * \param event The event object (passed to base-class implementation) 
     */
    virtual void closeEvent(QCloseEvent *event) override;

    private:

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
