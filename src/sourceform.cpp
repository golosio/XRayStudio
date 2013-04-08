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
#include <sstream>
#include "deviceinterf.h"
#include "mainwindow.h"
#include "xrs_error.h"
#include "deviceinspect.h"
#include "xrs_error.h"
#include "sourceform.h"
#include "ui_sourceform.h"
#include "xrmc_source.h"

SourceForm::SourceForm(DeviceInterf *di, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SourceForm)
{
    ui->setupUi(this);
    devInterf = di;
    devInterf->parentWindow->setEnabled(false);
    setAttribute(Qt::WA_DeleteOnClose);
    Source = dynamic_cast<source*>(di->devicePt);
    if (Source==0) {
        xrs_error(QString("Device ") + QString(di->devicePt->Name.c_str()) + " cannot be casted to type source!");
        close();
        return;
    }

    ui->thetaxEdit->setText(QString::number(Source->Thx));
    ui->thetayEdit->setText(QString::number(Source->Thy));

}

SourceForm::~SourceForm()
{
    devInterf->parentWindow->setEnabled(true);
    delete ui;
}

void SourceForm::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton stdButton = ui->buttonBox->standardButton(button);
    if (stdButton == QDialogButtonBox::Apply) {
        bool err_flag;
        double thx = ui->thetaxEdit->text().toDouble(&err_flag);
        if (!err_flag) {
            xrs_error("Error converting theta_x string to double!");
            close();
            return;
        }
        double thy = ui->thetayEdit->text().toDouble(&err_flag);
        if (!err_flag) {
            xrs_error("Error converting theta_y string to double!");
            close();
            return;
        }
        Source->Thx = thx;
        Source->Thy = thy;

        DeviceInspect::ApplyChanges(devInterf);
        close();
    }

}

int SourceForm::SaveDeviceForm(xrmc_device *dev_pt, std::ostream &dev_fs)
{
    source *s = dynamic_cast<source*>(dev_pt);
    if (s==0) {
        xrs_error(QString("Device ") + QString(dev_pt->Name.c_str()) + " cannot be casted to type source!");
        return 1;
    }
    dev_fs << "Divergence " << s->Thx << " " << s->Thy << endl;

    return 0;
}
