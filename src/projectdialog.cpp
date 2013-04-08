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
#include <QFileDialog>
#include <QPushButton>
#include <QRegExp>
#include "xrs_error.h"
#include "projectdialog.h"
#include "projtemplatedialog.h"
#include "warningdialog.h"
#include "ui_projectdialog.h"
#include "mainwindow.h"

ProjectDialog::ProjectDialog(MainWindow *w, QString proj_dir, bool new_proj_flag, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    mainWindow = w;
    newProjectFlag = new_proj_flag;
    ui->projectFolderEdit->setText(proj_dir);
    QPushButton *nextButton;
    if (newProjectFlag) nextButton = new QPushButton(tr("Next >"));
    else nextButton = new QPushButton(tr("Ok"));
    nextButton->setAutoDefault(true);
    nextButton->setDefault(true);
    ui->buttonBox->addButton(nextButton, QDialogButtonBox::ActionRole);
}

ProjectDialog::~ProjectDialog()
{
    delete ui;
}

void ProjectDialog::on_projectBrowseButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
             ui->projectFolderEdit->text().simplified(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dir!="" && QDir(dir).exists()) ui->projectFolderEdit->setText(dir);
}

void ProjectDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QString proj_name, proj_dir;
    QDialogButtonBox::StandardButton stdButton = ui->buttonBox->standardButton(button);
    if (stdButton != QDialogButtonBox::Cancel) {
        proj_name = ui->projectNameEdit->text().simplified();
        QRegExp rx("^[a-zA-Z0-9_\\.]+$");
        if(!rx.exactMatch(proj_name)) {
            xrs_error("Please insert a valid project name");
            return;
        }
        proj_dir = ui->projectFolderEdit->text().simplified();
        if (proj_dir=="") {
            xrs_error("Please insert a valid folder name");
            return;
        }
        QDir dir(proj_dir);
        if (!dir.exists()) {
            WarningDialog *cfd = new WarningDialog("Folder does not exist!\nDo you want to create it?");
            //xrs_error("Folder does dot exist");
            if (!cfd->exec()) return;
            else if(!dir.mkpath(".")) {
                xrs_error("Cannot create folder!");
                return;
            }
        }
        mainWindow->baseProjectFolder = proj_dir;
        proj_dir = proj_dir + "/" + proj_name;
        QDir dir1(proj_dir);
        if (dir1.exists()) {
            WarningDialog *efd = new WarningDialog(QString("Folder\n")+proj_dir+"\nalready exists!\nDo you want to overwrite it?");
            if (!efd->exec()) return;
        }
        else if(!dir1.mkpath(".")) {
            xrs_error("Cannot create folder!");
            return;
        }
        mainWindow->tmpProjectFolder = proj_dir;
        if (newProjectFlag) {
            ProjTemplateDialog *proj_templ = new ProjTemplateDialog(mainWindow);
            if (proj_templ->exec()) {
                mainWindow->projectName = proj_name;
                mainWindow->projectFolder = proj_dir;
                close();
            }
        }
        else {
            mainWindow->tmpProjectName = proj_name;
            mainWindow->tmpProjectFolder = proj_dir;
            close();
        }
    }
}
