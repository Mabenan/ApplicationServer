/*
 * Plugin.h
 *
 *  Created on: 02.03.2020
 *      Author: doene
 */

#ifndef REPS_APPLICATIONSERVER_APPLICATIONSERVERCORE_SRC_PLUGIN_H_
#define REPS_APPLICATIONSERVER_APPLICATIONSERVERCORE_SRC_PLUGIN_H_

#include <ApplicationServerCore_global.h>
#include <QxOrm.h>
class APPLICATIONSERVERCORE_EXPORT Plugin {

public:
  QString id;
  bool installed;

public:
  Plugin() {}
  virtual ~Plugin() = default;
  bool getInstalled() const;
  void setInstalled(bool value);
  QString getId() const;
  void setId(const QString &value);
};

QX_REGISTER_PRIMARY_KEY(Plugin, QString);
REGISTER_HPP_APPLICATIONSERVERCORE_LIBRARY(Plugin,
                                           qx::trait::no_base_class_defined, 0);

#endif /* REPS_APPLICATIONSERVER_APPLICATIONSERVERCORE_SRC_PLUGIN_H_ */
