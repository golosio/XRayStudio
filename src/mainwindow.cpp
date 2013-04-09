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
#include "mainwindow.h"
#include "connectdialog.h"
#include "deviceinterf.h"
#include "projectdialog.h"
#include "savechangesdialog.h"
#include "projtemplatedialog.h"
#include "xrs_error.h"
#include "ui_mainwindow.h"
#include "warningdialog.h"
#include <QFileDialog>
#include <QTextEdit>
#include <QPixmap>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QSplitter>
#include <QScrollArea>
#include "consoleform.h"
#include "rundialog.h"
#include "choosesavedevice.h"
#include "bannerdialog.h"
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    projectName = projectFolder = tmpProjectName = tmpProjectFolder;
    baseProjectFolder = "/home/golosio/qt/XRS/Projects";
    templateProjectFolder = "/home/golosio/qt/XRS/TemplateProjects";
    templateDeviceFolder = "/home/golosio/qt/XRS/TemplateDevices";;
    showMaximized();

    repaint();
    qApp->processEvents();
    console = new ConsoleForm(ui->consoleScrollArea->verticalScrollBar());
    iconDiagramWidget = new IconDiagramWidget(this);
    iconDiagram()->console = console;

    ui->consoleScrollArea->setWidget(console);
    QVBoxLayout *dataLayout = new QVBoxLayout();
    ui->consoleScrollArea->setLayout(dataLayout);
    console->resize(QSize(0.3*this->width(), ui->consoleScrollArea->height()-20));

    ui->diagramScrollArea->setWidget(iconDiagramWidget);
    QVBoxLayout *diagramLayout = new QVBoxLayout();
    ui->diagramScrollArea->setLayout(diagramLayout);
    iconDiagramWidget->resize(QSize(0.6*this->width(),  ui->diagramScrollArea->height()-20));
    QList<int> l;
    l.append(iconDiagramWidget->width());
    l.append(console->width());
    ui->mainSplitter->setSizes(l);
}

/*
void MainWindow::resizeEvent(QResizeEvent *e)
{
  // call the base method
  QMainWindow::resizeEvent(e);
  if (console) console->resize(QSize(console->width(), ui->consoleScrollArea->height()-10));
  emit signalResize(e);
}
*/

MainWindow::~MainWindow()
{
    console->close();
    delete ui;
}

IconDiagram *MainWindow::iconDiagram()
{
    return iconDiagramWidget->iconDiagram();
}

void MainWindow::on_actionSave_project_triggered()
{
    if (projectName=="") saveProjectAs();
    else {
        tmpProjectFolder = projectFolder;
        tmpProjectName = projectName;
        saveProject();
    }
}


void MainWindow::on_actionLoad_project_triggered()
{
    if (!isSaved()) {
        SaveChangesDialog *scd = new SaveChangesDialog(this);
        scd->exec();
        if (tmpProjectName=="") return;
    }
    tmpProjectFolder = projectFolder;
    tmpProjectName = projectName;
    LoadProject(baseProjectFolder);
    projectFolder = tmpProjectFolder;
    projectName = tmpProjectName;
    if (projectName!="") setWindowTitle(projectName + " - XRayStudio");
    else setWindowTitle("Untitled - XRayStudio");

}

int MainWindow::LoadProject(QString proj_folder)
{
    QString s = QFileDialog::getOpenFileName(this, tr("Choose a file..."), proj_folder, tr("XRS project files (*.xrs)"));
    if (s=="") return 1;
    QFileInfo fi(s);
    QString path = fi.absolutePath();
    ifstream ifs(s.toStdString().c_str());
    if (!ifs) {
        xrs_error("Can not open project file!");
        return 1;
    }
    tmpProjectFolder = path;
    tmpProjectName = fi.completeBaseName();
    int x, y;
    string name;
    iconDiagram()->clear();
    while (ifs >> name >> x >> y) {
        DeviceInterf *dev_interf = new DeviceInterf(this);
        if (dev_interf->LoadNewDevice(path.toStdString(), name, name)!=0) {
            delete dev_interf;
            ifs.close();
            return 1;
        }
        QPixmap pix(path+"/"+name.c_str()+".png");
        if (iconDiagramWidget->iconDiagram()->addIcon(x,y, dev_interf, QPixmap(pix))!=0) return 1;
        ifstream ilk(QString(path+"/"+name.c_str()+".ilk").toStdString().c_str());
        if (ilk) {
            dev_interf->LoadDevice(ilk);
            ilk.close();
        }
    }
    ifs.close();

    return 0;
}

void MainWindow::on_addDeviceButton_clicked()
{
    //here
    //console.show();
    QString s = QFileDialog::getOpenFileName(this, tr("Choose a file..."), templateDeviceFolder, tr("Device Files (*.png)"));
    if (s=="") return;
    QFileInfo fi(s);
    if (fi.suffix() != "png") {
        xrs_error("Invalid device files!");
        return;
    }

    QString name = fi.completeBaseName();
    DeviceInterf *dev_interf = new DeviceInterf(this);
    //if (dev_interf->Load(fi.absolutePath().toStdString(),name.toStdString())!=0) {
    //    delete dev_interf;
    //    return;
    //}
    bool used_name;
    QString dev_name = name.simplified(); dev_name.replace( " ", "_" );

    QString name1 = dev_name;
    int idx = 0;
    do {
        used_name = false;
        for (unsigned int j=0; j<iconDiagram()->icon.size(); j++) {
            if (name1.toStdString()==iconDiagram()->icon[j].name()) {
                used_name = true;
                idx++;
                name1 = dev_name + "_" + QString::number(idx);
                break;
            }
        }
    } while(used_name==true);
    if (dev_interf->LoadNewDevice(fi.absolutePath().toStdString()+"/.dev/", name.toStdString(), name1.toStdString())!=0) {
        delete dev_interf;
        return;
    }

    iconDiagram()->addIcon(50,50, dev_interf, QPixmap(s));

}

void MainWindow::on_actionNew_project_triggered()
{
    if (!isSaved()) {
        SaveChangesDialog *scd = new SaveChangesDialog(this);
        scd->exec();
        if (tmpProjectName=="") return;
    }
    ProjectDialog *proj_dialog = new ProjectDialog(this, baseProjectFolder, true);
    proj_dialog->exec();
    if (projectName!="") setWindowTitle(projectName + " - XRayStudio");
    else setWindowTitle("Untitled - XRayStudio");
    //projectDialog->show();
}

void MainWindow::on_actionSave_project_as_triggered()
{
    saveProjectAs();
}

int MainWindow::saveProjectAs()
{
    ProjectDialog *proj_dialog = new ProjectDialog(this, baseProjectFolder, false);
    tmpProjectName = "";
    proj_dialog->exec();
    if (tmpProjectName=="") return 1;
    projectFolder = tmpProjectFolder;
    projectName = tmpProjectName;
    if (saveProject()!=0) return 1;

    return 0;
}

int MainWindow::saveProject()
{
    QString s =  projectFolder+"/"+projectName+".xrs";
    if (projectName=="") {
        projectFolder = tmpProjectFolder;
        projectName = tmpProjectName;
        return 1;
    }
    if (deleteExistingProject()!=0) {
        projectFolder = tmpProjectFolder;
        projectName = tmpProjectName;
        xrs_error("Error removing old project files!");
        return 1;
    }
    ofstream ofs(s.toStdString().c_str());
    if (!ofs) {
        projectFolder = tmpProjectFolder;
        projectName = tmpProjectName;
        xrs_error("Cannot open project file for writing!");
        return 1;
    }
    for (unsigned int i=0; i<iconDiagram()->icon.size(); i++) {
        DeviceInterf *dev_interf = iconDiagram()->icon[i].devInterf;
        string name = dev_interf->devicePt->Name;
        dev_interf->Save(projectFolder.toStdString());
        QString pxpath = projectFolder + "/" + name.c_str() + ".png";
        iconDiagram()->icon[i].pixmap.save(pxpath);

        ofs << name << " " << iconDiagram()->icon[i].pos.x() << " " << iconDiagram()->icon[i].pos.y() << endl;
    }
    ofs.close();
    setWindowTitle(projectName + " - XRayStudio");

    return 0;
}


int MainWindow::deleteExistingProject()
{
    if (projectName=="") return 1;
    QString s = projectFolder+"/"+projectName+".xrs";
    //console->insertText(s+"\n");
    ifstream proj_file(s.toStdString().c_str());
    if(!proj_file) return 0;
    //console->insertText("proj exist \n");

    int x, y;
    string name;
    while (proj_file >> name >> x >> y) {
        //console->insertText(projectFolder+"/"+name.c_str()+".png");
        QFile f1(projectFolder+"/"+name.c_str()+".png");
        if(f1.exists()) {
            //console->insertText(" exists\n");
            f1.close();
            QFile::remove(projectFolder+"/"+name.c_str()+".png");
        }
        QFile f2(projectFolder+"/"+name.c_str()+".ilk");
        if(f2.exists()) {
            f2.close();
            QFile::remove(projectFolder+"/"+name.c_str()+".ilk");
        }
        QFile f3(projectFolder+"/"+name.c_str()+".frm");
        if(f3.exists()) {
            f3.close();
            QFile::remove(projectFolder+"/"+name.c_str()+".frm");
        }
        QFile f4(projectFolder+"/"+name.c_str()+".cmd");
        if(f4.exists()) {
            f4.close();
            QFile::remove(projectFolder+"/"+name.c_str()+".cmd");
        }
    }
    QFile::remove(projectFolder+"/"+projectName+".xrs");

    return 0;
}


bool MainWindow::isSaved()
{
    QString s =  projectFolder+"/"+projectName+".xrs";
    if (projectName=="") {
        if (iconDiagram()->icon.size() >0) return false;
        else return true;
    }

    ifstream ifs(s.toStdString().c_str());
    if (!ifs) {console->insertText(s+"\n"); return false;}
    int x, y;
    string name;
    int i=0;
    while (ifs >> name >> x >> y) {
        if (i>=(int)iconDiagram()->icon.size()) return false;
        DeviceInterf *dev_interf = iconDiagram()->icon[i].devInterf;
        if (name!=dev_interf->devicePt->Name) return false;
        if (iconDiagram()->icon[i].pos.x() != x) return false;
        if (iconDiagram()->icon[i].pos.y() != y) return false;
        QPixmap pix(projectFolder+"/"+name.c_str()+".png");
        if (!pix) return false;
        //if ((iconDiagram()->icon[i].pixmap)!=pix) return false;

        if (!dev_interf->isSaved(projectFolder.toStdString())) return false;
        i++;

    }
    ifs.close();

    return true;
}

void MainWindow::on_actionClose_project_triggered()
{
    if (!isSaved()) {
        SaveChangesDialog *scd = new SaveChangesDialog(this);
        scd->exec();
        if (tmpProjectName=="") return;
    }
    iconDiagram()->clear();
    projectName="";
    setWindowTitle("Untitled - XRayStudio");
}

void MainWindow::on_actionExit_triggered()
{
    if (!isSaved()) {
        SaveChangesDialog *scd = new SaveChangesDialog(this);
        scd->exec();
        if (tmpProjectName=="") return;
    }
    close();
}

void MainWindow::on_centralWidget_destroyed()
{
    if (!isSaved()) {
        SaveChangesDialog *scd = new SaveChangesDialog(this);
        scd->exec();
        if (tmpProjectName=="") return;
    }
    close();

}

void MainWindow::on_RunDeviceButton_clicked()
{
    RunDialog *rd = new RunDialog(iconDiagram(), this);
    for (unsigned int i=0; i<iconDiagram()->icon.size(); i++) {
        xrmc_device *dev_pt = iconDiagram()->icon[i].devInterf->devicePt;
        string name = dev_pt->Name;
        if (dev_pt->Runnable) rd->addItem(i, name.c_str());
    }
    rd->exec();
}


void MainWindow::on_saveDataButton_clicked()
{
    ChooseSaveDevice *sd = new ChooseSaveDevice(iconDiagram(), this);
    for (unsigned int i=0; i<iconDiagram()->icon.size(); i++) {
        xrmc_device *dev_pt = iconDiagram()->icon[i].devInterf->devicePt;
        string name = dev_pt->Name;
        for (unsigned int j=0; j<dev_pt->SaveDataName.size(); j++) {
            sd->addItem(i, j, (name + " : " + dev_pt->SaveDataName[j]).c_str());
        }
    }
    sd->exec();
}

void MainWindow::on_actionAbout_XRayStudio_triggered()
{
    BannerDialog *bann=new BannerDialog(this);
    bann->exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit mainWindowClosed();
    if (!isSaved()) {
        SaveChangesDialog *scd = new SaveChangesDialog(this);
        scd->exec();
        if (tmpProjectName=="") return;
    }
    event->accept();
}
/*
void MainWindow::mainWindowClosed()
{
    if (!isSaved()) {
        SaveChangesDialog *scd = new SaveChangesDialog(this);
        scd->exec();
        if (tmpProjectName=="") return;
    }
    close();
}
*/
int MainWindow::setBanner(QString bann_str)
{
    ui->bannerLabel->setText(bann_str);
    return 0;
}
