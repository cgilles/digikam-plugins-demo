/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2019-09-01
 * Description : Hello World demo BQM plugin.
 *
 * Copyright (C) 2019 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include "helloworldbqmplugin.h"

// Qt includes

#include <QApplication>

// Local includes

#include "helloworld.h"

namespace DigikamBqmHelloWorldPlugin
{

HelloWorldBqmPlugin::HelloWorldBqmPlugin(QObject* const parent)
    : DPluginBqm(parent)
{
}

HelloWorldBqmPlugin::~HelloWorldBqmPlugin()
{
}

QString HelloWorldBqmPlugin::name() const
{
    return QString::fromUtf8("Hello World");
}

QString HelloWorldBqmPlugin::iid() const
{
    return QLatin1String(DPLUGIN_IID);
}

QIcon HelloWorldBqmPlugin::icon() const
{
    return QIcon::fromTheme(QLatin1String("digikam"));
}

QString HelloWorldBqmPlugin::description() const
{
    return QString::fromUtf8("A demo tool Hello World");
}

QString HelloWorldBqmPlugin::details() const
{
    return QString::fromUtf8("<p>This Batch Queue Manager tool is a simple demo.</p>");
}

QList<DPluginAuthor> HelloWorldBqmPlugin::authors() const
{
    return QList<DPluginAuthor>()
            << DPluginAuthor(QString::fromUtf8("Gilles Caulier"),
                             QString::fromUtf8("caulier dot gilles at gmail dot com"),
                             QString::fromUtf8("(C) 2019"))
            ;
}

void HelloWorldBqmPlugin::setup(QObject* const parent)
{
    HelloWorld* const tool = new HelloWorld(parent);
    tool->setPlugin(this);

    addTool(tool);
}

} // namespace DigikamBqmHelloWorldPlugin
