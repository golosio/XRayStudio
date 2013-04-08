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
#ifndef DEVICECOMMANDS_H
#define DEVICECOMMANDS_H

#include <QDialog>
#include <QPlainTextEdit>
#include <QAbstractButton>

class DeviceInterf;

namespace Ui {
class DeviceCommands;
}

class DeviceCommands : public QDialog
{
    Q_OBJECT
    
public:
    DeviceInterf *devInterf;
    explicit DeviceCommands(DeviceInterf *di, QWidget *parent = 0);
    ~DeviceCommands();
    QPlainTextEdit *commandTextEdit();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DeviceCommands *ui;
};

#endif // DEVICECOMMANDs_H