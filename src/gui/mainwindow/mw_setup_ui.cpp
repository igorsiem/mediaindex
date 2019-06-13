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

#include "../mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setupUi(void)
{
    ui->setupUi(this);
    restoreWindowGeometry();
}   // end setupUi method
