/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2018-07-30
 * Description : image editor plugin HelloWorld demo.
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

#include "helloworldeditorplugin.h"

// Qt includes

#include <QApplication>
#include <QMessageBox>

namespace DigikamEditorHelloWorldEditorPlugin
{

HelloWorldEditorPlugin::HelloWorldEditorPlugin(QObject* const parent)
    : DPluginEditor(parent)
{
}

HelloWorldEditorPlugin::~HelloWorldEditorPlugin()
{
}

QString HelloWorldEditorPlugin::name() const
{
    return QString::fromUtf8("Hello World");
}

QString HelloWorldEditorPlugin::iid() const
{
    return QLatin1String(DPLUGIN_IID);
}

QIcon HelloWorldEditorPlugin::icon() const
{
    return QIcon::fromTheme(QLatin1String("digikam"));
}

QString HelloWorldEditorPlugin::description() const
{
    return QString::fromUtf8("A demo tool Hello World");
}

QString HelloWorldEditorPlugin::details() const
{
    return QString::fromUtf8("<p>This Image Editor tool is a simple demo.</p>");
}

QList<DPluginAuthor> HelloWorldEditorPlugin::authors() const
{
    return QList<DPluginAuthor>()
            << DPluginAuthor(QString::fromUtf8("Gilles Caulier"),
                             QString::fromUtf8("caulier dot gilles at gmail dot com"),
                             QString::fromUtf8("(C) 2019"))
            ;
}

void HelloWorldEditorPlugin::setup(QObject* const parent)
{
    DPluginAction* const ac = new DPluginAction(parent);
    ac->setIcon(icon());
    ac->setText(QString::fromUtf8("Hello World..."));
    ac->setObjectName(QLatin1String("editorwindow_helloworld"));
    ac->setActionCategory(DPluginAction::EditorColors);

    connect(ac, SIGNAL(triggered(bool)),
            this, SLOT(slotHelloWorld()));

    addAction(ac);
}

void HelloWorldEditorPlugin::slotHelloWorld()
{
    QMessageBox::information(qApp->activeWindow(),
                             qApp->applicationName(),
                             QString::fromUtf8("Hello World"));
}

} // namespace DigikamEditorHelloWorldEditorPlugin
