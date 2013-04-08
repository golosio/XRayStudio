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
#include <QKeyEvent>
#include "devicenameedit.h"
#include "icondiagram.h"

DeviceNameEdit::DeviceNameEdit(IconDiagram *idg, QWidget *parent)
    : QTextEdit(parent)
{
    iconDiagram = idg;
    iconIdx = -1;
}

void DeviceNameEdit::keyPressEvent(QKeyEvent *e)
{
    if (iconIdx<0) {
        hide();
        return;
    }
    switch (e->key()) {
        case Qt::Key_Return:
            iconDiagram->renameIcon(iconIdx, toPlainText());
            iconIdx = -1;
            hide();
        break;
        default:
            QTextEdit::keyPressEvent(e);
    }
}

void DeviceNameEdit::focusOutEvent (QFocusEvent* event )
{
    if (iconIdx<0) {
        hide();
        return;
    }
    iconDiagram->renameIcon(iconIdx, toPlainText());
    iconIdx = -1;
    hide();
    QTextEdit::focusOutEvent(event);
}
