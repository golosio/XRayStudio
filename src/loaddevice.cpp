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
//     loaddevice.cpp            //
//        06/02/2013             //
//   author : Bruno Golosio      //
///////////////////////////////////
// xrs method for loading device
//

#include "xrmc.h"
#include "xrmc_exception.h"
#include "xrmc_device.h"
#include "xrmc_gettoken.h"
#include "xrmc_spectrum.h"
#include "xrmc_source.h"
#include "xrmc_composition.h"
#include "xrmc_geom3d.h"
#include "xrmc_sample.h"
#include "xrmc_detector.h"
#include <QString>
#include <QTextStream>
#include <QTextEdit>
#include <QDebug>
#include <QFile>
#include "consoleform.h"
#include "mainwindow.h"
#include "xrs_error.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
//#include <stdlib.h>
using namespace std;
using namespace gettoken;

//////////////////////////////////////////////////////////////////////
// method for loading device
//////////////////////////////////////////////////////////////////////
int DeviceInterf::LoadNewDevice(string path, string file_name, string name_str)
{
    string input_path=path+"/"+file_name+".frm";
    ifstream input_file(input_path.c_str());
    if (!input_file) {
        xrs_error("Device form input file not found!");
        return 1;
    }
    int ierr=LoadDeviceForm(input_file, name_str);
    input_file.close();
    if (ierr!=0) return 1;
    input_path=path+"/"+file_name+".cmd";
    input_file.open(input_path.c_str());
    if (!input_file) {
        xrs_error(QString(input_path.c_str()) + " Device commands file not found!");
        return 1;
    }
    ierr = LoadDevice(input_file);
    input_file.close();
    if (ierr!=0) return 1;
    clearInputNames();
    ierr = LoadDeviceCommands(input_path);
    if (ierr!=0) return 1;

    input_path=path+"/"+file_name+".bnr";
    input_file.open(input_path.c_str());
    if (input_file) {
        stringstream oss;
        // do the copy:
        oss << input_file.rdbuf();
        banner = oss.str();
        input_file.close();
    }
    else banner = "";

    return 0;
}

int DeviceInterf::LoadDeviceForm(istream &dev_fs, string name_str)
{
  string comm="";
  std::stringstream buffer;
  std::streambuf *cout_bk = std::cout.rdbuf(buffer.rdbuf());

  QString error_message="";
  try {
      GetToken(dev_fs, comm); // read the command
      if (comm=="Newdevice") {
        // load device parameters from device file and initialize the device
        if (xrmc_device::LoadNewDevice(dev_fs, devicePt)!=0) {
            throw xrmc_exception(string("Error loading device\n"));
        }
      }
      else // unknown command
        throw xrmc_exception(string("Unrecognized command ") + comm +
                 " in device file.\n");

      std::string text = buffer.str(); // text will now contain load output
      console->insertText(QString(text.c_str()));
      devicePt->Name = name_str;
  }
  catch (xrmc_exception &e){ // handle possible runtime errors
      error_message = QString("Error: ") + e.what() + "\n";
  }
  catch (bad_alloc&) {
    error_message = "Error allocating memory.\n";
  }
  catch (...) {
    error_message = "Unrecognized error.\n";
  }
  std::cout.rdbuf(cout_bk);
  if (error_message != "") {
      console->textEdit()->setTextColor( QColor( "red" ) );
      console->insertText(error_message);
      console->textEdit()->setTextColor( QColor( "black" ) );
      xrs_error(QString(error_message));
      return 1;
  }

  return 0;
}

int DeviceInterf::LoadDevice(istream &dev_fs)
{
  string comm, dev_name;
  std::stringstream buffer;
  std::streambuf *cout_bk = std::cout.rdbuf(buffer.rdbuf());

  QString error_message="";
  try {
      GetToken(dev_fs, comm); // read the command
      if (comm=="Device") {
          GetToken(dev_fs, dev_name); // read dummy device name
        // load device parameters from device file
        if (devicePt->Load(dev_fs)!=0) {
            throw xrmc_exception(string("Error loading device\n"));
        }
      }
      else // unknown command
        throw xrmc_exception(string("Unrecognized command ") + comm +
                 " in device file.\n");

      std::string text = buffer.str(); // text will now contain load output
      console->insertText(QString(text.c_str()));
  }
  catch (xrmc_exception &e){ // handle possible runtime errors
      error_message = QString("Error: ") + e.what() + "\n";
  }
  catch (bad_alloc&) {
    error_message = "Error allocating memory.\n";
  }
  catch (...) {
    error_message = "Unrecognized error.\n";
  }
  std::cout.rdbuf(cout_bk);
  if (error_message != "") {
      console->textEdit()->setTextColor( QColor( "red" ) );
      console->insertText(error_message);
      console->textEdit()->setTextColor( QColor( "black" ) );
      xrs_error(QString(error_message));
      return 1;
  }

  return 0;
}

int DeviceInterf::clearInputNames()
{
  for (int idx=0; idx<devicePt->NInputDevices; idx++) {
      devicePt->InputDeviceName[idx] = "";
  }
    return 0;
}

int DeviceInterf::LoadDeviceCommands(string input_path)
{
    string comm, dev_name;

    ifstream dev_fs(input_path.c_str());
    GetToken(dev_fs, comm); // read the command
    if (comm=="Device") {
        GetToken(dev_fs, dev_name); // read dummy device name
        stringstream oss;
        // do the copy:
        oss << dev_fs.rdbuf();
        commands = oss.str();
    }
    else {
        xrs_error("Unrecognized command in device input file!");
        return 1;
    }
    dev_fs.close();

    return 0;
}
