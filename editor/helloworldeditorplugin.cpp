/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2019-07-30
 * Description : Hello World demo image editor plugin.
 *
 * Copyright (C) 2019-2024 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

// digiKam includes

#include <imageiface.h>
#include <dmessagebox.h>
#include <photoinfocontainer.h>

// Local includes

#include "i18nutils.h"

namespace DigikamEditorHelloWorldPlugin
{

HelloWorldEditorPlugin::HelloWorldEditorPlugin(QObject* const parent)
    : DPluginEditor(parent)
{
    s_initI18nResource();
    s_loadI18n(name());
}

HelloWorldEditorPlugin::~HelloWorldEditorPlugin()
{
    s_cleanupI18nResource();
}

QString HelloWorldEditorPlugin::name() const
{
    return tr("Hello World");
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
    return tr("A demo Hello World plugin");
}

QString HelloWorldEditorPlugin::details() const
{
    return tr("<p>This Image Editor plugin is a simple demo.</p>");
}

QList<DPluginAuthor> HelloWorldEditorPlugin::authors() const
{
    return QList<DPluginAuthor>()
            << DPluginAuthor(QString::fromUtf8("Gilles Caulier"),
                             QString::fromUtf8("caulier dot gilles at gmail dot com"),
                             QString::fromUtf8("(C) 2019-2024"))
            ;
}

void HelloWorldEditorPlugin::setup(QObject* const parent)
{
    DPluginAction* const ac = new DPluginAction(parent);
    ac->setIcon(icon());
    ac->setText(tr("Hello World (Editor)..."));
    ac->setObjectName(QLatin1String("editorwindow_helloworld"));
    ac->setActionCategory(DPluginAction::EditorColors);

    connect(ac, SIGNAL(triggered(bool)),
            this, SLOT(slotHelloWorld()));

    addAction(ac);
}

void HelloWorldEditorPlugin::slotHelloWorld()
{
    ImageIface iface;
    DImg* const image = iface.original();

    if (!image)
    {
        return;
    }

    PhotoInfoContainer inf = iface.originalPhotoInfo();

    QStringList props;
    props << tr("Size    : %1x%2").arg(image->width()).arg(image->height());
    props << tr("Format  : %1").arg(image->format());
    props << tr("16 bits : %1").arg(image->sixteenBit() ? QLatin1String("true") : QLatin1String("false"));
    props << tr("Alpha   : %1").arg(image->hasAlpha()   ? QLatin1String("true") : QLatin1String("false"));
    props << tr("Make    : %1").arg(inf.make);
    props << tr("Model   : %1").arg(inf.model);
    props << tr("Exposure: %1").arg(inf.exposureTime);
    props << tr("Aperture: %1").arg(inf.aperture);
    props << tr("Focal   : %1").arg(inf.focalLength);
    props << tr("Flash   : %1").arg(inf.flash);

    DMessageBox::showInformationList(QMessageBox::Information,
                                     qApp->activeWindow(),
                                     tr("Hello World (Editor)"),
                                     tr("Image properties:"),
                                     props);
}

} // namespace DigikamEditorHelloWorldPlugin
