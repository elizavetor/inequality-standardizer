QT = core

CONFIG += c++17 cmdline
QT += testlib
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        error.cpp \
        inequalitystandardizer.cpp \
        main.cpp \
        nodeofexprtree.cpp \
        operandofexpr.cpp \
        test_getdegreeofexpr.cpp \
        test_getlistofnodesofsameprecedencelevel.cpp \
        test_getnodesofsameprecedencewithparenthesesopening.cpp \
        test_getsortedlist.cpp \
        test_iscurrentorderofmultipliers.cpp \
        test_iscurrentorderofparenthesisedexpressions.cpp \
        test_iscurrentorderofsummands.cpp \
        test_listtotree.cpp \
        test_operatorgt.cpp \
        test_postfixtotree.cpp \
        test_sortoperandsalphabetically.cpp \
        test_treetoinfix.cpp \
        testingfunctions.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    error.h \
    nodeofexprtree.h \
    test_getdegreeofexpr.h \
    test_getlistofnodesofsameprecedencelevel.h \
    test_getnodesofsameprecedencewithparenthesesopening.h \
    test_getsortedlist.h \
    test_iscurrentorderofmultipliers.h \
    test_iscurrentorderofparenthesisedexpressions.h \
    test_iscurrentorderofsummands.h \
    test_listtotree.h \
    test_operatorgt.h \
    test_postfixtotree.h \
    test_sortoperandsalphabetically.h \
    test_treetoinfix.h \
    testingfunctions.h
