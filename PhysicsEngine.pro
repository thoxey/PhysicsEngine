TEMPLATE = app
TARGET = physics
CONFIG += debug
CONFIG += c++11
CONFIG -= app_bundle

OBJECTS_DIR = obj

QMAKE_CXXFLAGS += $$system(sdl2-config --cflags)

SOURCES += src/main.cpp \
    src/world.cpp \
    src/gameobject.cpp \
    src/staticcircle.cpp \
    src/dynamicobject.cpp \
    src/dynamiccircle.cpp \
    src/button.cpp \
    src/staticline.cpp \
    src/vector2d.cpp


HEADERS += \
    src/world.h \
    src/gameobject.h \
    src/staticcircle.h \
    src/dynamicobject.h \
    src/dynamiccircle.h \
    src/button.h \
    src/staticline.h \
    src/vector2d.h

linux: {
  LIBS += $$system(sdl2-config --libs)
  LIBS += -L/usr/local/lib/ -lSDL2  -lGLU -lGL -lSDL2_image -ljpeg
}


macx: {
  QMAKE_MAC_SDK = macosx10.12
  DEFINES+=MAC_OS_X_VERSION_MIN_REQUIRED=1060
  QMAKE_LFLAGS += -F/Library/Frameworks
  LIBS += -framework SDL2
  LIBS += -framework SDL2_image
  INCLUDEPATH += /Library/Frameworks/SDL2_image.framework/Headers
  INCLUDEPATH += /Library/Frameworks/SDL2.framework/Headers
  INCLUDEPATH += /usr/local/include
  LIBS+= -framework OpenGL
}

OTHER_FILES += *.png
