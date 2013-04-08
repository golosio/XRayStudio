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
#include <iostream>
#include "connectdialog.h"
#include "ui_connectdialog.h"
#include "icondiagram.h"
#include "mainwindow.h"
#include "xrs_error.h"
using namespace std;

ConnectDialog::ConnectDialog(IconDiagram *parent, int icon_idx) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    iconDiagram = parent;
    iconIdx = icon_idx;
    devInterf = parent->icon[icon_idx].devInterf;
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    inputEdit[0] = ui->inputEdit_1;
    inputEdit[1] = ui->inputEdit_2;
    inputEdit[2] = ui->inputEdit_3;
    inputEdit[3] = ui->inputEdit_4;
    inputEdit[4] = ui->inputEdit_5;
    inputEdit[5] = ui->inputEdit_6;
    inputLabel[0] = ui->inputLabel_1;
    inputLabel[1] = ui->inputLabel_2;
    inputLabel[2] = ui->inputLabel_3;
    inputLabel[3] = ui->inputLabel_4;
    inputLabel[4] = ui->inputLabel_5;
    inputLabel[5] = ui->inputLabel_6;

    setWindowTitle(QString(parent->icon[icon_idx].name().c_str()) + " input devices");
    int i;
    for (i=0; i<devInterf->devicePt->NInputDevices; i++) {
        inputLabel[i]->setText(QString(devInterf->devicePt->InputDeviceDescription[i].c_str()));
    }
    for (; i<6; i++) {
        inputLabel[i]->close();
        inputEdit[i]->close();
    }

    for (i=0; i<devInterf->devicePt->NInputDevices; i++) {
        inputEdit[i]->setText(QString(devInterf->devicePt->InputDeviceName[i].c_str()));
    }
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}


void ConnectDialog::on_buttonBox_accepted()
{
    xrmc_device_map device_map = devInterf->parentWindow->iconDiagram()->getDeviceMap();
    int Ninp = devInterf->devicePt->NInputDevices;
    string *tmp_name = new string[Ninp];
    for (int i=0; i<Ninp; i++) {
        tmp_name[i] = devInterf->devicePt->InputDeviceName[i];
        QString s = inputEdit[i]->text();
        s = s.simplified(); s.replace( " ", "" );
        devInterf->devicePt->InputDeviceName[i] = s.toStdString();
    }
    QString error_message="";
    try {
      devInterf->devicePt->LinkInputDevices(&device_map);
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
    if (error_message != "") {
        xrs_error(QString(error_message));
        for (int i=0; i<Ninp; i++) {
            devInterf->devicePt->InputDeviceName[i] = tmp_name[i];
        }
        close();
        return;
    }

    close();
}

void ConnectDialog::on_buttonBox_rejected()
{
    close();
}
