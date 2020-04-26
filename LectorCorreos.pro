QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agregar.cpp \
    avl_tree_primario.cpp \
    avl_tree_secundario.cpp \
    eliminar_copia.cpp \
    eliminar_propietario.cpp \
    indices.cpp \
    main.cpp \
    mainwindow.cpp \
    correo.cpp \
    lectorcorreo.cpp \
    modificar.cpp \
    modificar_copia.cpp \
    modificar_propietario.cpp \
    parser.cpp \
    sobrescribir.cpp \
    vistaprevia.cpp

HEADERS += \
    agregar.h \
    avl_tree_primario.h \
    avl_tree_secundario.h \
    eliminar_copia.h \
    eliminar_propietario.h \
    hash_map.h \
    indices.h \
    lsl.h \
    mainwindow.h \
    correo.h \
    lectorcorreo.h \
    modificar.h \
    modificar_copia.h \
    modificar_propietario.h \
    parser.h \
    sobrescribir.h \
    vector.h \
    vistaprevia.h

FORMS += \
    agregar.ui \
    eliminar_copia.ui \
    eliminar_propietario.ui \
    mainwindow.ui \
    modificar.ui \
    modificar_copia.ui \
    modificar_propietario.ui \
    sobrescribir.ui \
    vistaprevia.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
