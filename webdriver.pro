QT -= gui

TEMPLATE = lib
DEFINES += FDRIVER_LIBRARY
TARGET = webdriver
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
    webdriver/client.cpp \
    webdriver/detail/finder.cpp \
    webdriver/element.cpp \
    webdriver/session.cpp \
    webdriver/utils/webdriver_utils.cpp \
    webdriver/webdriver.cpp \
    webdriver/window.cpp

HEADERS += \
    webdriver/browsers/chrome.h \
    webdriver/browsers/firefox.h \
    webdriver/browsers/ie.h \
    webdriver/by.h \
    webdriver/capabilities.h \
    webdriver/client.h \
    webdriver/conversions.h \
    webdriver/detail/error_handling.h \
    webdriver/detail/factories.h \
    webdriver/detail/factories_impl.h \
    webdriver/detail/finder.h \
    webdriver/detail/http_client.h \
    webdriver/detail/http_connection.h \
    webdriver/detail/http_request.h \
    webdriver/detail/keyboard.h \
    webdriver/detail/meta_tools.h \
    webdriver/detail/resource.h \
    webdriver/detail/shared.h \
    webdriver/detail/time.h \
    webdriver/detail/to_string.h \
    webdriver/detail/types.h \
    webdriver/detail/picojson.h \
    webdriver/element.h \
    webdriver/errors.h \
    webdriver/js_args.h \
    webdriver/keys.h \
    webdriver/response_status_code.h \
    webdriver/session.h \
    webdriver/types.h \
    webdriver/utils/webdriver_utils.h \
    webdriver/wait.h \
    webdriver/wait_match.h \
    webdriver/webdriver.h \
    webdriver/webdriver_global.h \
    webdriver/window.h


INCLUDEPATH += $$PWD/curl/include
LIBS += -L$$PWD/curl/libs -llibcurl -llibcurl_imp

INCLUDEPATH += $$PWD/chilkat/include/
LIBS += -L$$PWD/chilkat/libs/ -lchilkat-9.5.0 -lws2_32 -lcrypt32 -ldnsapi

CONFIG(debug, debug|release) {
DEFINES += DEBUG_MODE
# install
target.path = $$PWD/release/libs/debug
INSTALLS += target
}

CONFIG(release, debug|release) {
# install
target.path = $$PWD/release/libs/release
INSTALLS += target
}
