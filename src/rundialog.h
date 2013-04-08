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
#ifndef RUNDIALOG_H
#define RUNDIALOG_H

#include <QDialog>
#include <QString>
#include <vector>

class IconDiagram;

namespace Ui {
class RunDialog;
}

class RunDialog : public QDialog
{
    Q_OBJECT
    
public:
    std::vector<int> iconIdx;
    IconDiagram *iconDiagram;
    explicit RunDialog(IconDiagram *id, QWidget *parent = 0);
    ~RunDialog();
    int addItem(int i, QString s);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::RunDialog *ui;
};

#endif // RUNDIALOG_H
