bin_PROGRAMS = xraystudio
# The final program is called "xraystudio"
#bin_PROGRAMS = xraystudio

# You have those .cpp files you wrote
# Remember to include the name of the resource file with the .cpp extension.
xraystudio_SOURCES = \
	choosesavedevice.cpp \
	connectdialog.cpp \
	consoleform.cpp \
	devicecommands.cpp \
	deviceinspect.cpp \
	deviceinterf.cpp \
	devicenameedit.cpp \
	devices.cpp \
	icondiagram.cpp \
	icondiagramwidget.cpp \
	loaddevice.cpp \
	main.cpp \
	mainwindow.cpp \
	projectdialog.cpp \
	projtemplatedialog.cpp \
	rundialog.cpp \
	savechangesdialog.cpp \
	savedevice.cpp \
	sourceform.cpp \
	warningdialog.cpp \
	xrs_error.cpp \
	bannerdialog.cpp

# You have one .h file, it's called myapp.h. Therefore, here I list
# its mocced name, moc_myapp.cpp.
nodist_xraystudio_SOURCES = \
        moc_choosesavedevice.cpp  \
        moc_connectdialog.cpp  \
        moc_consoleform.cpp  \
        moc_devicecommands.cpp  \
        moc_deviceinspect.cpp  \
        moc_deviceinterf.cpp  \
        moc_devicenameedit.cpp  \
        moc_icondiagram.cpp  \
        moc_icondiagramwidget.cpp  \
        moc_mainwindow.cpp  \
        moc_projectdialog.cpp  \
        moc_projtemplatedialog.cpp  \
        moc_rundialog.cpp  \
        moc_savechangesdialog.cpp  \
        moc_sourceform.cpp  \
        moc_ui_connectdialog.cpp  \
        moc_warningdialog.cpp  \
        moc_xrs_error.cpp \
	moc_bannerdialog.cpp

# This is to ensure the xraystudio.h file is distributed in your
# xraystudio-0.1.tar.gz
# I also have a resources.qrc I need to include. The png is used in myapp.
EXTRA_DIST = \
	$(nodist_xraystudio_SOURCES:moc_%.cpp=%.h) \
	resources.qrc
# myapp.png

# This rule lets GNU make create any moc_*.cpp from the equivalent *.h
moc_%.cpp: %.h
	moc $< -o $@

# Adjust this line according to your resources.qrc
resources.cpp : resources.qrc octave-gui.png
	rcc resources.qrc -o resources.cpp

# This line ensures that generated moc_*.cpp and resources.cpp files are
# deleted when we make clean.
CLEANFILES = $(filter moc_%.cpp,$(xraystudio_SOURCES)) resources.cpp

