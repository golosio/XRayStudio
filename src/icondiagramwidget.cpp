/*
Copyright (C) 2013 Bruno Golosio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "xrs_error.h"
#include "icondiagramwidget.h"
#include "ui_icondiagramwidget.h"
#include "mainwindow.h"

#include <QFileDialog>

IconDiagramWidget::IconDiagramWidget(MainWindow *w, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconDiagramWidget)
{
    ui->setupUi(this);
    mainWindow = w;
}

IconDiagramWidget::~IconDiagramWidget()
{
    delete ui;
}
IconDiagram *IconDiagramWidget::iconDiagram()
{
    return ui->iconDiagr;
}

