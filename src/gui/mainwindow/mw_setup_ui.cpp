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

#include <QAbstractItemView>
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

    // Set up the folder tree and file list view - their component objects
    // are retained as attributes of the `MainWindow`
    setupFolderTreeView();
    setupFileListView();

    auto leftRightSplt = new QSplitter(this);
    leftRightSplt->addWidget(m_foldersTrVw);
    leftRightSplt->addWidget(m_filesLstVw);

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

void MainWindow::setupFolderTreeView(void)
{
    m_foldersTrVw = new QTreeView();

    m_foldersMdl = new QFileSystemModel();
    m_foldersTrVw->setModel(m_foldersMdl);

    // Use root directory from last time, but make sure it still exists
    QString oldRootPath = rootDirectoryPath();
    QDir root(oldRootPath);
    if (!root.exists())
    {
        saveRootDirectoryPath(QDir::rootPath());

        logging::info("using root \"" + rootDirectoryPath() + "\" because "
            "previous root (\"" + oldRootPath + "\") does not exist");
    }

    logging::info("using root folder: " + rootDirectoryPath());

    m_foldersMdl->setFilter(
        QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);

    m_foldersTrVw->setColumnHidden(1, true);
    m_foldersTrVw->setColumnHidden(2, true);
    m_foldersTrVw->setColumnHidden(3, true);

    connect(
        m_foldersTrVw->selectionModel()
        , &QItemSelectionModel::currentChanged
        , [this](const QModelIndex& current, const QModelIndex& previous)
        { 
            emit selectedDirectoryChanged(m_foldersMdl->filePath(current));
        });

    handleRootDirectoryChanged(rootDirectoryPath());

    // Make sure that the tree view has the last selected path selected
    m_foldersTrVw->selectionModel()->setCurrentIndex(
        m_foldersMdl->index(
            selectedDirectoryPath())
            , QItemSelectionModel::Select);

}   // end setupFolderTree method

void MainWindow::setupFileListView(void)
{
    m_filesLstVw = new QListView();

    m_filesMdl = new QFileSystemModel();
    m_filesLstVw->setModel(m_filesMdl);

    // Use selected directory from last time. If it doesn't exist, we use the
    // root directory as selected directory (which has already been checked).
    QString oldSelDirPath = selectedDirectoryPath();
    QDir selDir(oldSelDirPath);
    if (!selDir.exists())
    {
        saveSelectedDirectoryPath(rootDirectoryPath());

        logging::info("using root directory path \"" + rootDirectoryPath()
            + "\" as selected directory path, because previous selected "
            "directory path (\"" + oldSelDirPath + "\") does not not exist");
    }

    logging::info("selected directory path: " + selectedDirectoryPath());

    m_filesMdl->setFilter(QDir::Files | QDir::NoDotAndDotDot);
    
    m_filesLstVw->setViewMode(QListView::IconMode);

    connect(
        m_filesLstVw->selectionModel()
        , &QItemSelectionModel::currentChanged
        , [this](const QModelIndex& current, const QModelIndex& previous)
        {
            logging::debug(
                "selected file: " + m_filesMdl->filePath(current));
        });

    handleSelectedDirectoryChanged(selectedDirectoryPath());
}   // end setupFileListView method
