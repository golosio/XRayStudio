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
#ifndef CHOOSESAVEDEVICE_H
#define CHOOSESAVEDEVICE_H

#include <QDialog>
#include <QString>
#include <vector>

class IconDiagram;

namespace Ui {
class ChooseSaveDevice;
}

class ChooseSaveDevice : public QDialog
{
    Q_OBJECT

public:
    std::vector<int> iconIdx;
    std::vector<int> dataIdx;
    IconDiagram *iconDiagram;
    explicit ChooseSaveDevice(IconDiagram *id, QWidget *parent = 0);
    ~ChooseSaveDevice();
    int addItem(int i, int j, QString s);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ChooseSaveDevice *ui;
};

#endif // CHOOSESAVEDEVICE_H
