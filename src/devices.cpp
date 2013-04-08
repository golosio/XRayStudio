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
#include <iostream>
#include "deviceinterf.h"
#include "icondiagram.h"
#include "deviceinspect.h"
#include "sourceform.h"
//#include "sampleform.h"

void IconDiagram::inspectDevice()
{
    DeviceInterf *di = icon[pressed_icon].devInterf;
    // ADD NEW DEVICE FORMS HERE:
    //if (di->devicePt->DeviceType=="source") {
    //    SourceForm *dev_insp = new SourceForm(di);
    //    dev_insp->show();
    //}
    //else if (di->devicePt->DeviceType=="sample") {
    //SampleForm *dev_insp = new SampleForm(di);
    //dev_insp->show();
    //}
    //else {
        DeviceInspect *dev_insp = new DeviceInspect(di);
        dev_insp->show();
	//}
}

int DeviceInterf::SaveDeviceForm(std::ostream &dev_fs)
{
    dev_fs << "Newdevice " << devicePt->DeviceType << " " << devicePt->Name << endl;
    //if (devicePt->DeviceType=="source") SourceForm::SaveDeviceForm(devicePt, dev_fs);
    //else if (devicePt->DeviceType=="sample") SampleForm::SaveDeviceForm(std::ostream &dev_fs);
    dev_fs << "End\n";

    return 0;
}

