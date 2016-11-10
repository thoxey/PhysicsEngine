#ifndef IMGUI_GLOBAL_H
#define IMGUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IMGUI_LIBRARY)
#  define IMGUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define IMGUISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // IMGUI_GLOBAL_H
