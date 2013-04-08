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
#ifndef CONNECT_DIALOG_H
#define CONNECT_DIALOG_H

//#include "icondiagram.h"
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <set>

class IconDiagram;
class DeviceInterf;
namespace Ui {
class ConnectDialog;
}
class ConnectDialog : public QDialog
{
    Q_OBJECT
    
public:
    IconDiagram *iconDiagram;
    int iconIdx;
    std::set<int> *fromArrow;
    DeviceInterf *devInterf;
    QLineEdit *inputEdit[6];
    QLabel *inputLabel[6];
    //explicit ConnectDialog(QWidget *parent = 0);
    explicit ConnectDialog(IconDiagram *parent, int icon_idx);
    ~ConnectDialog();
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECT_DIALOG_H
