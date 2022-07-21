QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG += c++17
INCLUDEPATH += F:/openCV/opencv/build/include
LIBS +=-L"F:/openCV/opencv/myBuild2/install/x64/mingw/lib"
LIBS +=  \
-lopencv_core455 \
-lopencv_highgui455 \
-lopencv_imgproc455 \
-lopencv_photo455 \
-lopencv_imgcodecs455\
-lopencv_videoio455


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    characterdictionary.cpp \
    converter.cpp \
    image2ASCIIConverter.cpp \
    main.cpp \
    mainwindow.cpp \
    webcamhandler.cpp

HEADERS += \
    characterdictionary.h \
    converter.h \
    image2ASCIIConverter.h \
    mainwindow.h \
    webcamhandler.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
