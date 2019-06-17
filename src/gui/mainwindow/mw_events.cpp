/**
 * \file mw_events.cpp
 * Implement event handlers and slot methods for the `MainWindow` class
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <QPixmap>

#include "../mainwindow.h"

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveWindowGeometry();
    QMainWindow::closeEvent(event);
}   // end closeEvent

void MainWindow::handleRootDirectoryChanged(QString newRootDirectory)
{
    m_foldersMdl->setRootPath(newRootDirectory);
    m_foldersTrVw->setRootIndex(m_foldersMdl->index(newRootDirectory));

    // m_foldersTrVw->expandAll();
}   // end handleRootDirectoryChanged method

void MainWindow::handleSelectedDirectoryChanged(QString newSelectedDirectory)
{
    logging::debug("selected directory is now: " + newSelectedDirectory);
    if (m_filesMdl)
    {
        m_filesMdl->setRootPath(newSelectedDirectory);

        if (m_filesLstVw)
            m_filesLstVw->setRootIndex(
                m_filesMdl->index(newSelectedDirectory));
    }
    
    saveSelectedDirectoryPath(newSelectedDirectory);
}   // end handleSelectedDirectoryChanged method

void MainWindow::handleFileSelected(QString filePath)
{
    logging::debug("selected file: " + filePath);

    m_displayedFilePath = filePath;
    redisplayFile();

}   // end handleFileSelected
