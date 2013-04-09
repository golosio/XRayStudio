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
#include "icondiagram.h"
#include "choosesavedevice.h"
#include "ui_choosesavedevice.h"
#include <vector>
#include <QListWidget>

ChooseSaveDevice::ChooseSaveDevice(IconDiagram *id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseSaveDevice)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    iconDiagram = id;
}

ChooseSaveDevice::~ChooseSaveDevice()
{
    delete ui;
}

int ChooseSaveDevice::addItem(int i, int j, QString s)
{
    ui->listWidget->addItem(new QListWidgetItem(s));
    iconIdx.push_back(i);
    dataIdx.push_back(j);
    if (ui->listWidget->currentRow()<0) ui->listWidget->setCurrentRow(0);

    return 0;
}

void ChooseSaveDevice::on_buttonBox_accepted()
{
    if (ui->listWidget->currentRow()<0) return;
    iconDiagram->pressed_icon = iconIdx[ui->listWidget->currentRow()];
    iconDiagram->saveDeviceData(dataIdx[ui->listWidget->currentRow()]);
}
