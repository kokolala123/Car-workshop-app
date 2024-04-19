QT       += core gui
QT += sql
QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_staff.cpp \
    bossuse.cpp \
    calender_query.cpp \
    choose_slots.cpp \
    delete_staff.cpp \
    item.cpp \
    main.cpp \
    mainwindow.cpp \
    repair.cpp \
    staffcalendar.cpp \
    status.cpp \
    ticket.cpp \
    ticket_basic_query.cpp

HEADERS += \
    add_staff.h \
    bossuse.h \
    calender_query.h \
    choose_slots.h \
    delete_staff.h \
    item.h \
    mainwindow.h \
    repair.h \
    repairdlg.h \
    staffcalendar.h \
    status.h \
    ticket.h \
    ticket_basic_query.h

FORMS += \
    add_staff.ui \
    bossuse.ui \
    calender_query.ui \
    choose_slots.ui \
    delete_staff.ui \
    item.ui \
    mainwindow.ui \
    repair.ui \
    staffcalendar.ui \
    status.ui \
    ticket.ui \
    ticket_basic_query.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
