/**
 * \file mw_commands.cpp
 * Funcitonality for executing User commands
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <QFileDialog>

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::executeFileOpenRootFolderAction(void)
{
    ACTION_TRY
    {
        auto newPath = QFileDialog::getExistingDirectory(
            this
            , tr("Open Root Folder")
            , rootDirectoryPath()
            , QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if (!newPath.isEmpty())
        {
            setRootDirectoryPath(newPath);

            QString msg = tr("Root folder:") + newPath;
            logging::info(msg);
            statusBar()->showMessage(msg, 5000);

            Error(tr("this functionality is not complete yet")).raise();
        }
        
    }
    ACTION_CATCH_DURING("Opening Root Folder");
}   // end executeFileOpenRootFolderAction method
