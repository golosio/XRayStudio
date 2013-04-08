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
#ifndef ICONDIAGRAM_H
#define ICONDIAGRAM_H

#include "xrmc_device.h"
#include "deviceinterf.h"
#include "consoleform.h"
#include <QFrame>
#include <QLabel>
#include "devicenameedit.h"
#include <QMainWindow>
#include <vector>
#include <set>

class QDragEnterEvent;
class QDropEvent;
class DragIcon;
class DragLabel;
class DeviceInterf;

class IconDiagram : public QFrame
{
    Q_OBJECT
public:
    ConsoleForm *console;
    std::vector<DragIcon> icon;
    int pressed_icon;
    DeviceNameEdit *deviceNameEdit;
    xrmc_device_map getDeviceMap(); // map of devices used by the simulation
    IconDiagram(QWidget *parent=0);
    int addIcon(int x, int y, DeviceInterf *di, QPixmap pm);
    int intersectIcon(QPoint pt);
    int drawArrow(QPainter &p, int i0, int i1);
    int drawArrowPoint(QPainter &p, int x0, int y0, int x1, int y1);
    void openIconMenu(int idx, QPoint pos);
    int findIcon(string dev_name);
    void clear();
    int renameIcon(int icon_idx, QString name);
    int saveDeviceData(int data_idx);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent * event);

private:
    //xrmc_device_map DeviceMap; // map of devices used by the simulation
    QAction *openConnectAct;
    QAction *runDeviceAct;
    QAction *saveDeviceDataAct;
    QAction *inspectAct;
    QAction *commandAct;
    QAction *deleteIconAct;
    QAction *renameDeviceAct;
    void createActions();

public slots:
    void openConnectDialog();
    void deleteIcon();
    void runDevice();
    void inspectDevice();
    void openCommandForm();
    void saveDeviceData();
    void renameDevice();

};

class DragIcon
{
public:
    DeviceInterf *devInterf;
    int index;
    QPoint pos;
    QPixmap pixmap;
    DragLabel *label;
    static const int width=100;
    ~DragIcon();
    string name();
    void set(DragLabel *lbl, DeviceInterf *di, QPixmap pm, int idx);
    void setLabel(DragLabel *lbl);
    void move(int x, int y);
    void move(QPoint pt);
    QPoint lineInters(int x1, int y1);
};

class DragLabel : public QLabel
{
public:
    int index;
    DragLabel(QWidget *parent=0);
    int setName(string name);
};

#endif
