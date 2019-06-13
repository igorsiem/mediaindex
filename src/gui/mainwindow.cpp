/**
 * \file mainwindow.cpp
 * Implement the main window class
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <QHBoxLayout>
#include <QLabel>

#include <fmt/format.h>
using namespace fmt::literals;

#include <api/api.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QSettings& settings, QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_settings(settings)
{
    ui->setupUi(this);

    // Restore window geometry from persistent settings
    m_settings.beginGroup("MainWindow");
    restoreGeometry(m_settings.value("geometry").toByteArray());
    restoreState(m_settings.value("state").toByteArray());
    m_settings.endGroup();

    // Add a label for the API version
    ui->centralWidget->setLayout(new QHBoxLayout(ui->centralWidget));
    ui->centralWidget->layout()->addWidget(
        new QLabel(
            QString::fromStdString(
                "API version: {}"_format(api::version()))));
}   // end constructor

MainWindow::~MainWindow()
{
    delete ui;
}   // end destructor

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Record window geometry in persistent settings
    m_settings.beginGroup("MainWindow");
    m_settings.setValue("geometry", saveGeometry());
    m_settings.setValue("windowState", saveState());
    m_settings.endGroup();    

    QMainWindow::closeEvent(event);
}   // end closeEvent
