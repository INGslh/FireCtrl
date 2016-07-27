RESOURCES += images.qrc

HEADERS += mainwindow.h view.h \
    item.h
SOURCES += main.cpp \
    chip.cpp
SOURCES += mainwindow.cpp view.cpp

QT += widgets
QT += serialport

qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/chip
INSTALLS += target

