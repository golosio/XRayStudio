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
#include "consoleform.h"
#include "ui_consoleform.h"
#include <qmath.h>

ConsoleForm::ConsoleForm(QScrollBar *sb, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleForm)
{
    ui->setupUi(this);
    verticalScrollBar = sb;
}

ConsoleForm::~ConsoleForm()
{
    delete ui;
}

//void ConsoleForm::on_textEdit_textChanged()
//{
//    resize(width(), ui->textEdit->document()->size().height() + 10);
//}

void ConsoleForm::insertText(QString s)
{
    ui->textEdit->insertPlainText(s);
    qreal h = qMax((qreal)height(), ui->textEdit->document()->size().height() + 10);
    resize(width(), h);
    verticalScrollBar->setValue(verticalScrollBar->maximum());
}
