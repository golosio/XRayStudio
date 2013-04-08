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
#include "savechangesdialog.h"
#include "mainwindow.h"
#include "ui_savechangesdialog.h"
#include <QAbstractButton>
SaveChangesDialog::SaveChangesDialog(MainWindow *w, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveChangesDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    mainWindow = w;
    ui->label->setText(ui->label->text()+"\n"+mainWindow->projectName+" ?");
    mainWindow->tmpProjectName="";
}

SaveChangesDialog::~SaveChangesDialog()
{
    delete ui;
}

void SaveChangesDialog::on_buttonBox_accepted()
{
    mainWindow->tmpProjectName=mainWindow->projectName;
    mainWindow->saveProject();
}


void SaveChangesDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton stdButton = ui->buttonBox->standardButton(button);
    if (stdButton != QDialogButtonBox::Cancel)
        mainWindow->tmpProjectName = mainWindow->projectName;
    close();
}
