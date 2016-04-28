TEMPLATE = app
TARGET = physics
CONFIG += debug


linux: {
  LIBS+=$$system(sdl2-config --libs)
  LIBS += -lSDL2  -lGLU -lGL -lSDL2_image  -L/usr/local/lib/
}


macx:
{
  DEFINES+=MAC_OS_X_VERSION_MIN_REQUIRED=1060
  QMAKE_LFLAGS += -F/Library/Frameworks
  LIBS += -framework SDL2
  LIBS += -framework SDL2_image
  INCLUDEPATH += /Library/Frameworks/SDL2_image.framework/Headers
  INCLUDEPATH += /Library/Frameworks/SDL2.framework/Headers
  INCLUDEPATH += /usr/local/include

  LIBS+= -framework OpenGL
}

QMAKE_CXXFLAGS += $$system(sdl2-config --cflags)
LIBS += $$system(sdl2-config --libs)

OBJECTS_DIR = obj

CONFIG += c++11

SOURCES += src/main.cpp \
    src/world.cpp \
    src/gameobject.cpp \
    src/staticcircle.cpp \
    src/dynamicobject.cpp \
    src/dynamiccircle.cpp \
    src/button.cpp

HEADERS += \
    src/world.h \
    src/gameobject.h \
    src/staticcircle.h \
    src/dynamicobject.h \
    src/dynamiccircle.h \
    src/button.h
