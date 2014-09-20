#ifndef QMYO_GLOBAL_H
#define QMYO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QMYO_LIBRARY)
#  define QMYOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMYOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QMYO_GLOBAL_H
