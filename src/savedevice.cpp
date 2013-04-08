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
///////////////////////////////////
//     savedevice.cpp            //
//        01/04/2013             //
//   author : Bruno Golosio      //
///////////////////////////////////
// xrs method for loading device
//

#include "consoleform.h"
#include <sstream>
#include <iterator>
#include <fstream>
#include <string>
#include "deviceinterf.h"
#include "xrs_error.h"

using namespace std;

int DeviceInterf::Save(string path)
{
    string devpath=path+"/"+devicePt->Name+".frm";
    ofstream dev_fs(devpath.c_str());
    if (!dev_fs) {
        xrs_error(QString(devpath.c_str()) + " Can not open device .FRM output file!");
        return 1;
    }
    SaveDeviceForm(dev_fs);
    dev_fs.close();

    devpath=path+"/"+devicePt->Name+".cmd";
    dev_fs.open(devpath.c_str());
    if (!dev_fs) {
        xrs_error(QString(devpath.c_str()) + " Can not open device .CMD output file!");
        return 1;
    }
    SaveDeviceCommands(dev_fs);
    dev_fs.close();

    devpath=path+"/"+devicePt->Name+".ilk";
    dev_fs.open(devpath.c_str());
    if (!dev_fs) {
        xrs_error(QString(devpath.c_str()) + " Can not open device .ILK output file!");
        return 1;
    }
    SaveDeviceLinks(dev_fs);
    dev_fs.close();

    return 0;
}

int DeviceInterf::SaveDeviceCommands(ostream &dev_fs)
{
    dev_fs << "Device " << devicePt->Name << endl;
    dev_fs << commands;
    //dev_fs << "End\n";

    return 0;
}


int DeviceInterf::SaveDeviceLinks(ostream &dev_fs)
{
    dev_fs << "Device " << devicePt->Name << endl;
    for (int i=0; i<devicePt->NInputDevices; i++) {
        string s = devicePt->InputDeviceName[i];
        if (s!="") {
            dev_fs << devicePt->InputDeviceCommand[i] << " " << s << endl;
        }
    }
    dev_fs << "End\n";

    return 0;
}

bool DeviceInterf::isSaved(string path)
{
    string devpath=path+"/"+devicePt->Name+".cmd";
    ifstream dev_fs(devpath.c_str());
    if (!dev_fs) return false;
    string s1(istreambuf_iterator<char>(dev_fs.rdbuf()),
                istreambuf_iterator<char>());
    dev_fs.close();
    stringstream dev_ss2;
    SaveDeviceCommands(dev_ss2);
    string s2 = dev_ss2.str();
    if (s1 != s2) return false;

    devpath=path+"/"+devicePt->Name+".frm";
    dev_fs.open(devpath.c_str());
    if (!dev_fs) return false;
    s1=string(istreambuf_iterator<char>(dev_fs.rdbuf()),
                istreambuf_iterator<char>());
    dev_fs.close();
    dev_ss2.str("");
    SaveDeviceForm(dev_ss2);
    s2 = dev_ss2.str();
    if (s1 != s2) return false;

    devpath=path+"/"+devicePt->Name+".ilk";
    dev_fs.open(devpath.c_str());
    if (!dev_fs) return false;
    s1=string(istreambuf_iterator<char>(dev_fs.rdbuf()),
                istreambuf_iterator<char>());
    dev_fs.close();
    dev_ss2.str("");
    SaveDeviceLinks(dev_ss2);
    s2 = dev_ss2.str();
    if (s1 != s2) return false;

    return true;
}
