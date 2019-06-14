/**
 * \file mw_setup_ui.cpp
 * Functionality for setting up the User Interface of the `MainWindow`
 * class
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <QFrame>
#include <QVBoxLayout>

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setupUi(void)
{
    ui->setupUi(this);
    setWindowTitle("MediaIndex");
    
    restoreWindowGeometry();

    setupCentralWidget();
}   // end setupUi method

void MainWindow::setupCentralWidget(void)
{
    new QVBoxLayout(centralWidget());
    centralWidget()->layout()->addWidget(createLeftRightSplitter());
}   // end setupCentralWidget

QSplitter* MainWindow::createLeftRightSplitter(void)
{

    // Set up the folder tree - its component objects are retained as
    // attributes of the `MainWindow`
    setupFolderTree();

    // A temporary frame for the right-hand side, until we sort out what's
    // going on there.
    auto rightFrm = new QFrame(this);
    rightFrm->setFrameStyle(QFrame::Box);  

    auto leftRightSplt = new QSplitter(this);
    leftRightSplt->addWidget(m_foldersTrVw);
    leftRightSplt->addWidget(rightFrm);

    // Get splitter component sizes from persistent storage, and ensure that
    // they are saved there when the sizes change.
    m_settings.beginGroup("MainWindow");
    auto
        leftSize = m_settings.value("leftRightSplitterLeft", 50).toInt()
        , rightSize =
            m_settings.value("leftRightSplitterRight", 1000).toInt();
    m_settings.endGroup();
    leftRightSplt->setSizes(QList<int>({leftSize, rightSize}));

    connect(
        leftRightSplt
        , &QSplitter::splitterMoved
        , [this, leftRightSplt](int, int)
        {
            auto sizes = leftRightSplt->sizes();
            m_settings.beginGroup("MainWindow");
            m_settings.setValue("leftRightSplitterLeft", sizes[0]);
            m_settings.setValue("leftRightSplitterRight", sizes[1]);
            m_settings.endGroup();
        });

    return leftRightSplt;

}   // end createLeftRightSplitter method

void MainWindow::setupFolderTree(void)
{
    m_foldersTrVw = new QTreeView();

    m_foldersMdl = new QFileSystemModel();
    m_foldersTrVw->setModel(m_foldersMdl);

    logging::info("using root folder: " + rootDirectoryPath());

    m_foldersMdl->setFilter(
        QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);

    m_foldersTrVw->setColumnHidden(1, true);
    m_foldersTrVw->setColumnHidden(2, true);
    m_foldersTrVw->setColumnHidden(3, true);

    handleRootDirectoryChanged(rootDirectoryPath());
}   // end setupFolderTree method
