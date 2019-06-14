/**
 * \file mw_setup_actions.cpp
 * Functionality for setting up the actions system of the `MainWindow` class,
 * including the menu and toolbar
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <QAction>
#include <QKeySequence>

#include "../logging.h"
#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setupActions(void)
{

    // Some initial tool bar setup
    ui->mainToolBar->setFloatable(false);
    ui->mainToolBar->setMovable(false);
    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    setupFileActions();
}   // end setupActions method

void MainWindow::setupFileActions(void)
{
    auto openRootFolderAction =
        new QAction(tr("&Open Root Folder..."), this);
    openRootFolderAction->setShortcut(QKeySequence::StandardKey::Open);

    connect(
        openRootFolderAction
        , &QAction::triggered
        , [this](void)
        { 
            logging::logger().log(
                logging::level_t::debug
                , L"open root folder called");
            executeFileOpenRootFolderAction();
        });

    auto fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openRootFolderAction);

    ui->mainToolBar->addAction(openRootFolderAction);
}   // end setupFileActions method
