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
#ifndef SAVECHANGESDIALOG_H
#define SAVECHANGESDIALOG_H

#include <QDialog>
#include <QAbstractButton>
class MainWindow;
namespace Ui {
class SaveChangesDialog;
}

class SaveChangesDialog : public QDialog
{
    Q_OBJECT
    
public:
    MainWindow *mainWindow;
    explicit SaveChangesDialog(MainWindow *w, QWidget *parent = 0);
    ~SaveChangesDialog();
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::SaveChangesDialog *ui;
};

#endif // SAVECHANGESDIALOG_H
