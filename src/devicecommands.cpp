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
#include <QPlainTextEdit>
#include <QAbstractButton>
#include "devicecommands.h"
#include "ui_devicecommands.h"
#include "mainwindow.h"
#include "xrs_error.h"
#include <string>
#include <sstream>

DeviceCommands::DeviceCommands(DeviceInterf *di, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceCommands)
{
    ui->setupUi(this);
    devInterf = di;
    devInterf->parentWindow->setEnabled(false);
    setAttribute(Qt::WA_DeleteOnClose);
}

DeviceCommands::~DeviceCommands()
{
    devInterf->parentWindow->setEnabled(true);
    delete ui;
}

QPlainTextEdit *DeviceCommands::commandTextEdit()
{
    return ui->commandTextEdit;
}

void DeviceCommands::on_buttonBox_clicked(QAbstractButton *button)
{

    QDialogButtonBox::StandardButton stdButton = ui->buttonBox->standardButton(button);
    if (stdButton == QDialogButtonBox::Apply) {
        xrmc_device *tmpDevice=devInterf->devicePt;
        xrmc_device_map device_map = devInterf->parentWindow->iconDiagram()->getDeviceMap();
        xrmc_device_map::iterator it = device_map.find(tmpDevice->Name);
         // check that the device was defined in device map
        if (it==device_map.end()) {
            xrs_error(QString("Device ") + QString(tmpDevice->Name.c_str()) + " not found in device map!");
            close();
            return;
        }

        stringstream ss;
        devInterf->SaveDeviceForm(ss);
        if (devInterf->LoadDeviceForm(ss, tmpDevice->Name)!=0) {
            devInterf->devicePt = tmpDevice;
            //xrs_error("Error loading temporary device file!"); //error message already displayed!
            close();
            return;
        }
        string comm_head = "Device " + tmpDevice->Name + "\n";
        string comm = commandTextEdit()->toPlainText().toStdString();
        istringstream iss(comm_head + comm + "\nEnd\n");
        if (devInterf->LoadDevice(iss)!=0) {
            devInterf->devicePt = tmpDevice;
            //xrs_error("Error loading temporary device file!"); //error message already displayed!
            close();
            return;
        }
        devInterf->commands = comm;
        for (int idx=0; idx<devInterf->devicePt->NInputDevices; idx++) {
            devInterf->devicePt->InputDeviceName[idx] = tmpDevice->InputDeviceName[idx];
        }
        close();
    }
}
