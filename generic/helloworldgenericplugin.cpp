/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2019-07-30
 * Description : Hello World demo generic plugin.
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

#include "helloworldgenericplugin.h"

// Qt includes

#include <QApplication>
#include <QMessageBox>
#include <QList>
#include <QUrl>
#include <QTranslator>
#include <QLocale>

// digiKam includes

#include <dinfointerface.h>
#include <dmessagebox.h>

// NOTE: need to be done outside plugin namespace.
void s_initResource()
{
    Q_INIT_RESOURCE(i18n);
}

void s_cleanupResource()
{
    Q_CLEANUP_RESOURCE(i18n);
}

namespace DigikamGenericHelloWorldPlugin
{

HelloWorldPlugin::HelloWorldPlugin(QObject* const parent)
    : DPluginGeneric(parent)
{
    s_initResource();
    loadTranslations();
}

HelloWorldPlugin::~HelloWorldPlugin()
{
    s_cleanupResource();
}

QString HelloWorldPlugin::name() const
{
    return tr("Hello World");
}

QString HelloWorldPlugin::iid() const
{
    return QLatin1String(DPLUGIN_IID);
}

QIcon HelloWorldPlugin::icon() const
{
    return QIcon::fromTheme(QLatin1String("digikam"));
}

QString HelloWorldPlugin::description() const
{
    return tr("A demo Hello World plugin");
}

QString HelloWorldPlugin::details() const
{
    return tr("<p>This Generic plugin is a simple demo.</p>");
}

QList<DPluginAuthor> HelloWorldPlugin::authors() const
{
    return QList<DPluginAuthor>()
            << DPluginAuthor(QString::fromUtf8("Gilles Caulier"),
                             QString::fromUtf8("caulier dot gilles at gmail dot com"),
                             QString::fromUtf8("(C) 2019"))
    ;
}

void HelloWorldPlugin::setup(QObject* const parent)
{
    DPluginAction* const ac = new DPluginAction(parent);
    ac->setIcon(icon());
    ac->setText(tr("Hello World (Generic)..."));
    ac->setObjectName(QLatin1String("HelloWorld"));
    ac->setActionCategory(DPluginAction::GenericTool);

    connect(ac, SIGNAL(triggered(bool)),
            this, SLOT(slotHelloWorld()));

    addAction(ac);
}

void HelloWorldPlugin::slotHelloWorld()
{
    DInfoInterface* const iface = infoIface(sender());
    QList<QUrl> images          = iface->currentSelectedItems();
    QString caption             = tr("List of current selected items (%1):").arg(images.count());

    if (images.isEmpty())
    {
        images  = iface->currentAlbumItems();
        caption = tr("List of all items (%1):").arg(images.count());

    }

    if (!images.isEmpty())
    {
        QStringList items;

        foreach (const QUrl& url, images)
        {
            items << url.url();
        }

        DMessageBox::showInformationList(QMessageBox::Information,
                                         qApp->activeWindow(),
                                         tr("Hello World (Generic)"),
                                         caption,
                                         items);
    }
}

bool HelloWorldPlugin::loadTranslation(const QString& lang) const
{
    qDebug() << "Loading i18n" << lang << "for plugin" << name();

    QTranslator* const i18n = new QTranslator(qApp);

    if (!i18n->load(QString::fromLatin1(":/i18n/%1.qm").arg(lang)))
    {
        delete i18n;
        return false;
    }

    qApp->installTranslator(i18n);

    return true;
}

void HelloWorldPlugin::loadTranslations()
{
    // Quote from ecm_create_qm_loader created code:
    // The way Qt translation system handles plural forms makes it necessary to
    // have a translation file which contains only plural forms for `en`.
    // That's why we load the `en` translation unconditionally, then load the
    // translation for the current locale to overload it.
    const QString en(QStringLiteral("en"));

    loadTranslation(en);

    QLocale locale = QLocale::system();

    if (locale.name() != en)
    {
        if (!loadTranslation(locale.name()))
        {
            loadTranslation(locale.bcp47Name());
        }
    }
}

} // namespace DigikamGenericHelloWorldPlugin
