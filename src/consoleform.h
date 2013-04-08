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
#ifndef CONSOLEFORM_H
#define CONSOLEFORM_H

#include <QWidget>
#include <QTextEdit>
#include <QScrollBar>
#include "ui_consoleform.h"

namespace Ui {
class ConsoleForm;
}

class ConsoleForm : public QWidget
{
    Q_OBJECT
    
public:
    QScrollBar *verticalScrollBar;
    explicit ConsoleForm(QScrollBar *sb, QWidget *parent = 0);
    ~ConsoleForm();
    QTextEdit *textEdit() {
        return ui->textEdit;
    }
    void insertText(QString s);

private slots:
//    void on_textEdit_textChanged();

private:
    Ui::ConsoleForm *ui;
};
//namespace console
//{
//    static ConsoleForm *form;
//}
#endif // CONSOLEFORM_H
