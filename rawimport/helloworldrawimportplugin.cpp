/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2019-09-09
 * Description : Hello World demo image editor plugin.
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

#include "helloworldrawimportplugin.h"

// Qt includes

#include <QApplication>
#include <QProcess>
#include <QFileInfo>
#include <QDebug>

namespace DigikamRawImportHelloWorldPlugin
{

HelloWorldRawImportPlugin::HelloWorldRawImportPlugin(QObject* const parent)
    : DPluginRawImport(parent)
{
}

HelloWorldRawImportPlugin::~HelloWorldRawImportPlugin()
{
}

QString HelloWorldRawImportPlugin::name() const
{
    return QString::fromUtf8("Hello World");
}

QString HelloWorldRawImportPlugin::iid() const
{
    return QLatin1String(DPLUGIN_IID);
}

QIcon HelloWorldRawImportPlugin::icon() const
{
    return QIcon::fromTheme(QLatin1String("digikam"));
}

QString HelloWorldRawImportPlugin::description() const
{
    return QString::fromUtf8("A demo Hello World plugin");
}

QString HelloWorldRawImportPlugin::details() const
{
    return QString::fromUtf8("<p>This Raw Import plugin is a simple demo.</p>");
}

QList<DPluginAuthor> HelloWorldRawImportPlugin::authors() const
{
    return QList<DPluginAuthor>()
            << DPluginAuthor(QString::fromUtf8("Gilles Caulier"),
                             QString::fromUtf8("caulier dot gilles at gmail dot com"),
                             QString::fromUtf8("(C) 2019"))
            ;
}

void HelloWorldRawImportPlugin::setup(QObject* const parent)
{
    // TODO Check dcraw availability.
}

bool HelloWorldRawImportPlugin::run(const QString& filePath, const DRawDecoding& def)
{
    QFileInfo fi(filePath);
    qDebug() << "HelloWorldRawImportPlugin :: converting" << fi.fileName() << "using dcraw CLI tool...";

    QProcess::execute(QLatin1String("dcraw"), QStringList() << QLatin1String("-v")
                                                            << QLatin1String("-4")
                                                            << QLatin1String("-T")
                                                            << filePath);
    LoadingDescription props(fi.path() + QLatin1Char('/') + fi.completeBaseName() + QLatin1String(".tiff"),
                             LoadingDescription::ConvertForEditor);

    emit signalDecodedImage(props);
}

} // namespace DigikamRawImportHelloWorldPlugin
