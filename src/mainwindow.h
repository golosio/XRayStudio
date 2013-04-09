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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include <QCloseEvent>
#include "icondiagram.h"
//#include "consoleform.h"
#include "icondiagramwidget.h"

class ProjectDialog;
class ProjTemplateDialog;
class ConsoleForm;
namespace Ui {
class MainWindow;
}
class IconDiagram;
class MainWindow : public QMainWindow
{
    Q_OBJECT

/*
signals:
   void signalResize(QResizeEvent *);

protected:
   void resizeEvent(QResizeEvent *);  // virtual
*/

public:
    QString projectName;
    QString projectFolder;
    QString tmpProjectName;
    QString tmpProjectFolder;
    QString baseProjectFolder;
    QString templateProjectFolder;
    QString templateDeviceFolder;

    IconDiagramWidget *iconDiagramWidget;
    ConsoleForm *console;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    IconDiagram *iconDiagram();
    int LoadProject(QString proj_folder);
    int deleteExistingProject();
    int saveProjectAs();
    int saveProject();
    bool isSaved();
    int setBanner(QString bann_str);

private slots:

    void on_actionSave_project_triggered();

    void on_actionLoad_project_triggered();

    void on_addDeviceButton_clicked();

    void on_actionNew_project_triggered();

    void on_actionSave_project_as_triggered();

    void on_actionClose_project_triggered();

    void on_actionExit_triggered();

    void on_centralWidget_destroyed();

    void on_RunDeviceButton_clicked();

    void on_saveDataButton_clicked();

    void on_actionAbout_XRayStudio_triggered();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
signals:
    void mainWindowClosed();

};

#endif // MAINWINDOW_H
