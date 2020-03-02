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

template<> void register_class(QxClass<Plugin> &t) {
	t.setName("t_plugin");
	t.id(&Plugin::id, "plugin_id");
	t.data(&Plugin::installed, "installed");
}
}

Plugin::Plugin() {
	this->installed = false;
}

Plugin::~Plugin() {
}
