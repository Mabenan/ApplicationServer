#ifndef APPLICATIONSERVERINTERFACE_EXPORT_H
#define APPLICATIONSERVERINTERFACE_EXPORT_H
#include <QtCore/qglobal.h>
#if defined(BUILDAPPLICATIONSERVERINTERFACE)
 #define APPLICATION_SERVER_INTERFACE Q_DECL_EXPORT
#else
 #define APPLICATION_SERVER_INTERFACE Q_DECL_IMPORT
#endif
#endif // APPLICATIONSERVERINTERFACE_EXPORT_H
