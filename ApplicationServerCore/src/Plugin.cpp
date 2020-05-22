/*
 * Plugin.cpp
 *
 *  Created on: 02.03.2020
 *      Author: doene
 */

#include <Plugin.h>
#include <QxOrm_Impl.h>

REGISTER_CPP_APPLICATIONSERVERCORE_LIBRARY(Plugin)
namespace qx {

template <> void register_class(QxClass<Plugin> &t) {
  t.setName(QStringLiteral("t_plugin"));
  t.id(&Plugin::id, QStringLiteral("plugin_id"));
  t.data(&Plugin::installed, QStringLiteral("installed"));
}
} // namespace qx

bool Plugin::getInstalled() const { return installed; }

void Plugin::setInstalled(bool value) { installed = value; }

QString Plugin::getId() const { return id; }

void Plugin::setId(const QString &value) { id = value; }
