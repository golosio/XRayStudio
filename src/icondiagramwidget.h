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
#ifndef ICONDIAGRAMWIDGET_H
#define ICONDIAGRAMWIDGET_H

#include <QWidget>
#include "icondiagram.h"

namespace Ui {
class IconDiagramWidget;
}

class IconDiagramWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit IconDiagramWidget(MainWindow *w, QWidget *parent = 0);
    ~IconDiagramWidget();
    IconDiagram *iconDiagram();
    MainWindow *mainWindow;
private slots:

private:
    Ui::IconDiagramWidget *ui;
};

#endif // ICONDIAGRAMWIDGET_H
