/**
 * \file mw_utils.cpp
 * Implement some utility methods in the `MainWindow` class
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <QStandardPaths>
#include "../mainwindow.h"

void MainWindow::saveWindowGeometry(void)
{
    m_settings.beginGroup("MainWindow");
    m_settings.setValue("geometry", saveGeometry());
    m_settings.setValue("windowState", saveState());
    m_settings.endGroup();    
}   // end saveWindowGeometry method

void MainWindow::restoreWindowGeometry(void)
{
    m_settings.beginGroup("MainWindow");
    restoreGeometry(m_settings.value("geometry").toByteArray());
    restoreState(m_settings.value("state").toByteArray());
    m_settings.endGroup();
}   // end restoreWindowGeometry method

QString MainWindow::rootDirectoryPath(void) const
{
    m_settings.beginGroup("Directories");
    auto p = m_settings.value(
        "rootDirectoryPath"
        , QStandardPaths::PicturesLocation);
    m_settings.endGroup();

    return p.toString();
}   // end rootDirectoryPath method

void MainWindow::setRootDirectoryPath(QString p)
{
    m_settings.beginGroup("Directories");
    m_settings.setValue("rootDirectoryPath", p);
    m_settings.endGroup();
}   // end setRootDirectoryPath method
