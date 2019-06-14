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
#include <QSplitter>
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

    // Left / right frames and splitter
    auto leftFrm = new QFrame(this), rightFrm = new QFrame(this);
    leftFrm->setFrameStyle(QFrame::Box);
    rightFrm->setFrameStyle(QFrame::Box);  

    // -- 
    
    new QVBoxLayout(leftFrm);
    m_foldersTrVw = new QTreeView(leftFrm);
    leftFrm->layout()->addWidget(m_foldersTrVw);

    m_foldersMdl = new QFileSystemModel();
    m_foldersTrVw->setModel(m_foldersMdl);

    auto dirPath = rootDirectoryPath();
    logging::debug("using dir path: " + dirPath);
    m_foldersMdl->setRootPath(dirPath);
    m_foldersTrVw->setRootIndex(m_foldersMdl->index(dirPath));

    m_foldersMdl->setFilter(
        QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);

    // ---

    auto leftRightSplt = new QSplitter(this);
    leftRightSplt->addWidget(leftFrm);
    leftRightSplt->addWidget(rightFrm);

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

    centralWidget()->layout()->addWidget(leftRightSplt);
}   // end setupCentralWidget
