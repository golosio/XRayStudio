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
#ifndef DEVICEINTERF_H
#define DEVICEINTERF_H

#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include "xrmc_device.h"
//#include "consoleform.h"
//#include "deviceform.h"

class ConsoleForm;
class MainWindow;
class DeviceForm;

typedef std::pair<std::string,std::string> stringPair;
class DeviceInterf
{
public:
    MainWindow *parentWindow;
    ConsoleForm *console;
    //std::vector<std::string> devType;
    //std::vector<stringPair> inputType;
    //std::vector<string> inputCommand;
    xrmc_device *devicePt;
    //DeviceForm *deviceForm;
    string commands;
    string banner;
    DeviceInterf(MainWindow *w);
    //int Load(std::string path, std::string name);
    int Save(std::string path);
    int LoadNewDevice(std::string path, std::string file_name, std::string name_str);
    int LoadDeviceForm(std::istream &fs, std::string name_str);
    int LoadDevice(std::istream &fs);
    int LoadDeviceCommands(std::string input_path);
    int SaveDeviceForm(std::ostream &fs);
    int SaveDeviceCommands(std::ostream &fs);
    int SaveDeviceLinks(std::ostream &fs);

    int clearInputNames();
    bool isSaved(string path);

};

#endif // DEVICEINTERF_H
