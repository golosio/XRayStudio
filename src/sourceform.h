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
#ifndef SOURCEFORM_H
#define SOURCEFORM_H

#include <iostream>
#include <QDialog>
#include <QAbstractButton>

class DeviceInterf;
class xrmc_device;
class source;

namespace Ui {
class SourceForm;
}

class SourceForm : public QDialog
{
    Q_OBJECT
    
public:
    DeviceInterf *devInterf;
    source *Source;
    explicit SourceForm(DeviceInterf *di, QWidget *parent = 0);
    ~SourceForm();
    static int SaveDeviceForm(xrmc_device*dev_pt, std::ostream &dev_fs);
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::SourceForm *ui;
};

#endif // SOURCEFORM_H
