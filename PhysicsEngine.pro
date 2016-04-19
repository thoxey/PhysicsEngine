TEMPLATE = app
TARGET = physics
CONFIG += debug
INCLUDEPATH += /Library/Frameworks/SDL2.framework
linux : LIBS += -lSDL2 -lglut -lGLU -lGL
macx: {
  DEFINES+=MAC_OS_X_VERSION_MIN_REQUIRED=1060
  QMAKE_LFLAGS += -F/Library/Frameworks
  LIBS += -framework SDL2
  INCLUDEPATH += /Library/Frameworks/SLD2_image.framework
  INCLUDEPATH += /Library/Frameworks/SLD2_mixer.framework
  INCLUDEPATH += /Library/Frameworks/SDL2.framework/Headers
  INCLUDEPATH += /usr/local/include

  LIBS+= -framework OpenGL
}
OBJECTS_DIR = obj

CONFIG += c++11

SOURCES += src/main.cpp \
    src/world.cpp \
    src/gameobject.cpp \
    src/staticcircle.cpp \
    src/dynamicobject.cpp \
    src/dynamiccircle.cpp \
    src/staticsquare.cpp

HEADERS += \
    src/world.h \
    src/gameobject.h \
    src/staticcircle.h \
    src/dynamicobject.h \
    src/dynamiccircle.h \
    src/staticsquare.h
