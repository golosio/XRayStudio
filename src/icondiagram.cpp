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
#include <QtGui>
#include <QPalette>
#include "devicenameedit.h"
#include <QTextCursor>
#include "connectdialog.h"
#include "icondiagram.h"
#include "mainwindow.h"
#include "choosesavedevice.h"
#include "xrs_error.h"
#include "deviceinspect.h"
#include "devicecommands.h"
#include <sstream>
#include <iostream>

DragIcon::~DragIcon() {
    //label->close();
}

string DragIcon::name()
{
    return devInterf->devicePt->Name;
}

void DragIcon::set(DragLabel *lbl, DeviceInterf *di, QPixmap pm, int idx)
{
    devInterf = di;
    index = idx;
    pixmap = pm;
    setLabel(lbl);
}

void DragIcon::setLabel(DragLabel *lbl)
{
    label = lbl;
    label->setFixedWidth(width);
    label->index = index;
    label->setStyleSheet("color: black; background-color: rgba(0,0,0,0%)");
    label->setName(name());
}

void DragIcon::move(int x, int y)
{
    pos = QPoint(x,y);
    label->move(x-width/2,y+pixmap.width()/2);
    label->show();
}

void DragIcon::move(QPoint pt)
{
    move(pt.x(),pt.y());
}


DragLabel::DragLabel(QWidget *parent) : QLabel(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
}

int DragLabel::setName(string dev_name)
{
    QString htmlText = "<p align=\"center\">";
    QString line_text = "";
    unsigned int n = 0;
    while (n<dev_name.length()) {
        QFontMetrics fm(font());
        int w = fm.width(line_text + dev_name[n]);
        if (w>width()) {
            htmlText = htmlText + line_text + "<br>";
            line_text = dev_name[n];
        }
        else line_text = line_text + dev_name[n];
        n++;
    }
    htmlText = htmlText + line_text + "</p>";
    setText(htmlText);

    return 0;
}

 IconDiagram::IconDiagram(QWidget *parent)
     : QFrame(parent)
 {
     setMinimumSize(200, 200);
     setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
     setAcceptDrops(true);
     createActions();
     deviceNameEdit=new DeviceNameEdit(this, this);
     deviceNameEdit->setFixedHeight(50);
     //deviceNameEdit->setStyleSheet("margin: 0px");
     deviceNameEdit->setFrameShape(QFrame::NoFrame);
     //deviceNameEdit->setAlignment(Qt::AlignCenter);
     //deviceNameEdit->setLineWrapMode(QTextEdit::NoWrap);
     deviceNameEdit->hide();

 }

int IconDiagram::addIcon(int x, int y, DeviceInterf *di, QPixmap pm)
{
    string dev_name = di->devicePt->Name;
    if(findIcon(dev_name)>=0) {
        xrs_error(QString("Device name ") + dev_name.c_str() + " already used!");
        return 1;
    }
    DragIcon drag_icon;
    DragLabel *lbl = new DragLabel(this);
    drag_icon.set(lbl, di, pm, icon.size());
    drag_icon.move(x, y);
    icon.push_back(drag_icon);
    //DeviceMap.insert(xrmc_device_map_pair(drag_icon.name(), di->devicePt));

    return 0;
}

 void IconDiagram::dragEnterEvent(QDragEnterEvent *event)
 {
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void IconDiagram::dragMoveEvent(QDragMoveEvent *event)
 {
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void IconDiagram::dropEvent(QDropEvent *event)
 {
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
         QDataStream dataStream(&itemData, QIODevice::ReadOnly);

         int idx;
         QString path;
         QString text;
         QPoint offset;
         dataStream >> idx >> offset;

         DragLabel *label = new DragLabel(this);
         icon[idx].setLabel(label);
         for (unsigned int j=0; j<icon.size(); j++) {
             if ((int)j==idx) icon[j].label->setStyleSheet("color: white; background-color: rgba(100,150,200,255)");
             else icon[j].label->setStyleSheet("color: black; background-color: rgba(0,0,0,0%)");
         }
         icon[idx].move(event->pos() - offset + QPoint((label->width())/2,-icon[idx].pixmap.height()/2));
         label->show();
         repaint();

         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void IconDiagram::mousePressEvent(QMouseEvent *event)
 {
     deviceNameEdit->hide();

     DragLabel *child = static_cast<DragLabel*>(childAt(event->pos()));
     int idx;
     if (!child) {
         idx=intersectIcon(event->pos());
         if (idx<0) return;
         else child=icon[idx].label;
    }
    else idx = child->index;
    Qt::MouseButtons mouseButtons = event->buttons();
    if( mouseButtons == (Qt::RightButton) ) {
        openIconMenu(idx, event->globalPos()); //event->pos());
        return;
    }
     QPixmap pixmap = icon[idx].pixmap;
     QByteArray itemData;
     QDataStream dataStream(&itemData, QIODevice::WriteOnly);
     dataStream << idx << QPoint(event->pos() - child->pos());
     QMimeData *mimeData = new QMimeData;
     mimeData->setData("application/x-dnditemdata", itemData);
     QDrag *drag = new QDrag(this);
     drag->setMimeData(mimeData);
     drag->setPixmap(pixmap);
     drag->setHotSpot(event->pos() - child->pos() - QPoint((child->width()-pixmap.width())/2,-pixmap.height()));

     child->setStyleSheet("color: white; background-color: rgba(100,150,200,255)");
     //child->show();

     if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
         child->close();
     }
     //else {
        //child->set(path,text);
        //child->show();
     //}
 }

void IconDiagram::paintEvent(QPaintEvent *e)
{
   QFrame::paintEvent(e);

   QPainter p;
   p.begin(this);
   for(unsigned int i=0; i<icon.size(); i++) {
       int x=icon[i].pos.x();
       int y=icon[i].pos.y();
       QPixmap pm=icon[i].pixmap;
       p.drawPixmap(x-pm.width()/2,y-pm.height()/2,pm.width(),pm.height(),pm);
   }
   QPen pen(Qt::blue, 2); // blue solid line, 2 pixels wide
   p.setPen(pen); // set the blue, wide pen
   for (unsigned int i=0; i<icon.size(); i++) {
       //for (std::set<int>::iterator it=icon[i].fromArrow.begin(); it!=icon[i].fromArrow.end(); ++it) {
       //    drawArrow(p, *it, i);
       //}
       int Ninp = icon[i].devInterf->devicePt->NInputDevices;
       for (int ia=0; ia<Ninp; ia++) {
           int j = findIcon(icon[i].devInterf->devicePt->InputDeviceName[ia]);
           if (j>=0) drawArrow(p, j, i);
       }
   }
   p.end();
}

int IconDiagram::intersectIcon(QPoint pt)
{
    int i;
    for (i=icon.size()-1; i>=0; i--) {
        int x = icon[i].pos.x();
        int y = icon[i].pos.y();
        int hw = icon[i].pixmap.width()/2;
        int hh = icon[i].pixmap.height()/2;
        if (pt.x()>=x-hw && pt.x()<=x+hw && pt.y()>=y-hh && pt.y()<=y+hh) return i;
    }
    return -1;
}

QPoint DragIcon::lineInters(int x1, int y1)
{
    int xr = x1 - pos.x();
    int yr = y1 - pos.y();
    int hw = pixmap.width()/2;
    int hh = pixmap.height()/2;
    int x2=0, y2=0;
    if (xr!=0) {
        y2 = hw*yr/abs(xr);
        if (y2>hh) y2=hh;
        if (y2<-hh) y2=-hh;
    }
    else if (yr>0) y2=hh;
    else if (yr<0) y2=-hh;
    if (yr!=0) {
        x2 = hh*xr/abs(yr);
        if (x2>hw) x2=hw;
        if (x2<-hw) x2=-hw;
    }
    else if (xr>0) x2=hw;
    else if (xr<0) x2=-hw;

    return QPoint(pos.x()+x2, pos.y()+y2);
}

int IconDiagram::drawArrow(QPainter &p, int i0, int i1)
{
    int x0=icon[i0].pos.x();
    int y0=icon[i0].pos.y();
    int x1=icon[i1].pos.x();
    int y1=icon[i1].pos.y();
    QPoint pt0 = icon[i0].lineInters(x1, y1);
    QPoint pt1 = icon[i1].lineInters(x0, y0);
    x0 = pt0.x();
    y0 = pt0.y();
    x1 = pt1.x();
    y1 = pt1.y();

    p.drawLine(x0,y0,x1,y1);
    drawArrowPoint(p, x0, y0, x1, y1);

    return 0;
}

int IconDiagram::drawArrowPoint(QPainter &p, int x0, int y0, int x1, int y1)
{
    const double l=20, w=5;
    int xr = x0 - x1;
    int yr = y0 - y1;

    double mod = sqrt((double)xr*xr+yr*yr);
    int xp = -yr;
    int yp = xr;
    int xa = x1 + (int)(l*xr/mod) + (int)(w*xp/mod);
    int ya = y1 + (int)(l*yr/mod) + (int)(w*yp/mod);
    int xb = x1 + (int)(l*xr/mod) - (int)(w*xp/mod);
    int yb = y1 + (int)(l*yr/mod) - (int)(w*yp/mod);
    QPolygon triangle;

    triangle.clear();
    triangle << QPoint(x1, y1);
    triangle << QPoint(xa, ya);
    triangle << QPoint(xb, yb);
    QBrush blueBrush("blue",Qt::SolidPattern);
    p.setBrush(blueBrush);
    p.drawPolygon(triangle);

    return 0;
}

void IconDiagram::openConnectDialog()
{
    ConnectDialog *dial = new ConnectDialog(this,  pressed_icon);
    dial->setAttribute(Qt::WA_DeleteOnClose);
    dial->show();
}

void IconDiagram::runDevice()
{
    xrmc_device *dev_pt = icon[pressed_icon].devInterf->devicePt;
    xrmc_device_map device_map = getDeviceMap();
    std::stringstream buffer;
    std::streambuf *cout_bk = std::cout.rdbuf(buffer.rdbuf());
    QString error_message="";
    try {
        dev_pt->RecursiveLink(&device_map); // recursive link
        dev_pt->RecursiveRunInit(); // recursive run initialization
        dev_pt->Run(); // launch the Run method on the device
    }
    catch (xrmc_exception &e){ // handle possible runtime errors
        error_message = QString("Error: ") + e.what() + "\n";
    }
    catch (bad_alloc&) {
      error_message = "Error allocating memory.\n";
    }
    catch (...) {
      error_message = "Unrecognized error.\n";
    }
    std::cout.rdbuf(cout_bk);
    if (error_message != "") {
        console->textEdit()->setTextColor( QColor( "red" ) );
        console->insertText(error_message);
        console->textEdit()->setTextColor( QColor( "black" ) );
        xrs_error(QString(error_message));
        return;
    }
    console->insertText("Run complete\n");
}


void IconDiagram::openCommandForm()
{
    DeviceCommands *dc = new DeviceCommands(icon[pressed_icon].devInterf);
    dc->commandTextEdit()->clear();
    dc->commandTextEdit()->appendPlainText(icon[pressed_icon].devInterf->commands.c_str());
    dc->show();

}

void IconDiagram::saveDeviceData()
{
    xrmc_device *dev_pt = icon[pressed_icon].devInterf->devicePt;
    if (dev_pt->SaveDataName.size()>1) {
        ChooseSaveDevice *sd = new ChooseSaveDevice(this, this);
        for (unsigned int i=0; i<icon.size(); i++) {
            xrmc_device *dev_pt = icon[i].devInterf->devicePt;
            string name = dev_pt->Name;
            for (unsigned int j=0; j<dev_pt->SaveDataName.size(); j++) {
                sd->addItem(i, j, (name + " : " + dev_pt->SaveDataName[j]).c_str());
            }
        }
        sd->exec();
        return;
    }
    else saveDeviceData(0);
}

int IconDiagram::saveDeviceData(int data_idx)
{
    xrmc_device *dev_pt = icon[pressed_icon].devInterf->devicePt;

    std::stringstream buffer;
    std::streambuf *cout_bk = std::cout.rdbuf(buffer.rdbuf());
    QString error_message="";
    try {
        QString s = QFileDialog::getSaveFileName(this, tr("Choose a file..."), tr("/home/golosio/"));
        if (s=="") return 1;
        string file_name=s.toStdString();
        dev_pt->SaveData(dev_pt->SaveDataName[data_idx],file_name); // launch the Save method on the device
    }
    catch (xrmc_exception &e){ // handle possible runtime errors
        error_message = QString("Error: ") + e.what() + "\n";
    }
    catch (bad_alloc&) {
      error_message = "Error allocating memory.\n";
    }
    catch (...) {
      error_message = "Unrecognized error.\n";
    }
    std::cout.rdbuf(cout_bk);
    if (error_message != "") {
        console->textEdit()->setTextColor( QColor( "red" ) );
        console->insertText(error_message);
        console->textEdit()->setTextColor( QColor( "black" ) );
        xrs_error(QString(error_message));
        return 1;
    }

    console->insertText("Data saved\n");
    return 0;
}

void IconDiagram::deleteIcon()
{
    string dev_name = icon[pressed_icon].name();
    for (unsigned int i=0; i<icon.size(); i++) {
        int Ninp = icon[i].devInterf->devicePt->NInputDevices;
        for (int ia=0; ia<Ninp; ia++) {
            if (icon[i].devInterf->devicePt->InputDeviceName[ia]==dev_name)
                icon[i].devInterf->devicePt->InputDeviceName[ia]="";
        }
    }
    delete icon[pressed_icon].devInterf;
    icon[pressed_icon].label->close();
    icon.erase(icon.begin()+pressed_icon);

    repaint();
}

void IconDiagram::createActions()
{
    openConnectAct = new QAction(tr("&Connect"), this);
    //newAct->setShortcuts(QKeySequence::New);
    //newAct->setStatusTip(tr("Create a new file"));
    connect(openConnectAct, SIGNAL(triggered()), this, SLOT(openConnectDialog()));
    runDeviceAct = new QAction(tr("&Run"), this);
    connect(runDeviceAct, SIGNAL(triggered()), this, SLOT(runDevice()));
    saveDeviceDataAct = new QAction(tr("&Save data..."), this);
    connect(saveDeviceDataAct, SIGNAL(triggered()), this, SLOT(saveDeviceData()));
    inspectAct = new QAction(tr("&Inspect..."), this);
    connect(inspectAct, SIGNAL(triggered()), this, SLOT(inspectDevice()));
    commandAct = new QAction(tr("&Commands..."), this);
    connect(commandAct, SIGNAL(triggered()), this, SLOT(openCommandForm()));
    deleteIconAct = new QAction(tr("&Delete"), this);
    connect(deleteIconAct, SIGNAL(triggered()), this, SLOT(deleteIcon()));
    renameDeviceAct = new QAction(tr("&Rename"), this);
    connect(renameDeviceAct, SIGNAL(triggered()), this, SLOT(renameDevice()));
}

void IconDiagram::openIconMenu(int idx, QPoint pos)
{
    pressed_icon = idx;
    QMenu* menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    if (icon[idx].devInterf->devicePt->NInputDevices>0) {
        menu->addAction(openConnectAct);
    }
    menu->addAction(deleteIconAct);
    if (icon[idx].devInterf->devicePt->Runnable==true) {
        menu->addAction(runDeviceAct);
    }
    //for (int is=0; is<icon[idx].devInterf->devicePt->SaveDataName.size(); is++) {
    if (icon[idx].devInterf->devicePt->SaveDataName.size()>0) {
        menu->addAction(saveDeviceDataAct);
    }
    menu->addAction(renameDeviceAct);
    menu->addAction(inspectAct);
    menu->addAction(commandAct);
    menu->exec(pos);
    delete menu;
}

xrmc_device_map IconDiagram::getDeviceMap()
{
    xrmc_device_map device_map;
    for(unsigned int i=0; i<icon.size(); i++) {
        device_map.insert(xrmc_device_map_pair(icon[i].name(), icon[i].devInterf->devicePt));
    }

    return device_map;
}

int IconDiagram::findIcon(string dev_name)
{
    for(unsigned int i=0; i<icon.size(); i++) {
        if (icon[i].name()==dev_name) return i;
    }
    return -1;
}

void IconDiagram::clear()
{
    while (icon.size()>0) {
        delete icon[0].devInterf;
        icon[0].label->close();
        icon.erase(icon.begin());
    }
    repaint();
}

void IconDiagram::renameDevice()
{
    int x=icon[pressed_icon].pos.x() - icon[pressed_icon].width/2;
    int y=icon[pressed_icon].pos.y() + icon[pressed_icon].pixmap.width()/2;
    deviceNameEdit->setFixedWidth(icon[pressed_icon].width);
    //label->setStyleSheet("color: black; background-color: rgba(0,0,0,0%)");
    //label->setName(name());
    deviceNameEdit->iconIdx = pressed_icon;
    deviceNameEdit->move(x,y);//x-width/2,y+pixmap.width()/2);
    deviceNameEdit->clear();
    deviceNameEdit->insertPlainText(icon[pressed_icon].devInterf->devicePt->Name.c_str());
    deviceNameEdit->show();
    deviceNameEdit->raise();
    deviceNameEdit->setFocus();
}


int IconDiagram::renameIcon(int icon_idx, QString name)
{
    string new_name = name.toStdString();
    string old_name = icon[icon_idx].name();
    if (new_name==old_name) return 0;
    QRegExp rx("^[a-zA-Z0-9_\\.]+$");
    if(!rx.exactMatch(name)) {
        xrs_error("Please insert a valid device name");
        return 1;
    }
    if (findIcon(new_name)>=0) {
        xrs_error(QString("Device name ") + name + " already used!");
        return 1;
    }

    //icon[icon_idx].label->setName(name.toStdString());

    for (unsigned int i=0; i<icon.size(); i++) {
        int Ninp = icon[i].devInterf->devicePt->NInputDevices;
        for (int ia=0; ia<Ninp; ia++) {
            if (icon[i].devInterf->devicePt->InputDeviceName[ia]==old_name)
                icon[i].devInterf->devicePt->InputDeviceName[ia]=new_name;
        }
    }
    icon[icon_idx].devInterf->devicePt->Name=new_name;

    delete icon[icon_idx].label;
    DragLabel *label = new DragLabel(this);
    icon[icon_idx].setLabel(label);
    icon[icon_idx].label->setStyleSheet("color: white; background-color: rgba(100,150,200,255)");
    icon[icon_idx].move(icon[icon_idx].pos.x(), icon[icon_idx].pos.y());
    label->show();
    repaint();

    return 0;
}
