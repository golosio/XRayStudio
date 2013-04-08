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
#include <QtGui/QApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "icondiagram.h"
#include "consoleform.h"
#include "xraylib.h"

int main(int argc, char *argv[])
{
    XRayInit();
    QApplication a(argc, argv);
    MainWindow w;

    w.setAttribute(Qt::WA_DeleteOnClose);
    //IconDiagram *dw = w.iconDiagram();
    //dw->addIcon(":/images/sphere.png", "device0",120,250);
    //dw->addIcon(":/images/sphere.png", "device1",300,70);
    //dw->addIcon(":/images/sphere.png", "device2",70,300);
    //dw->addIcon(":/images/sphere.png", "device3",400,250);
    //dw->addIcon(":/images/sphere.png", "This is a test with line breaks",350,350);
    //dw->addArrow(0,2);
    //dw->addArrow(0,4);
    //dw->addArrow(2,4);
    w.showMaximized();
    //w.show();
    //w.console = new ConsoleForm();
    //w.console->show();
    //w.iconDiagram()->console = w.console;
    //console::form->textEdit()->insertPlainText("prova00\n");

    return a.exec();
}
