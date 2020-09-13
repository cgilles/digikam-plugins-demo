/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2019-09-01
 * Description : Hello World batch tool.
 *
 * Copyright (C) 2019-2020 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include "helloworld.h"

// Qt includes

#include <QWidget>
#include <QLabel>

// Local includes

#include "dimg.h"

namespace DigikamBqmHelloWorldPlugin
{

HelloWorld::HelloWorld(QObject* const parent)
    : BatchTool(QLatin1String("HelloWorld"), ColorTool, parent)
{
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::registerSettingsWidget()
{
    m_settingsWidget = new QWidget;
    new QLabel(tr("Hello World (Bqm)"), m_settingsWidget);

    BatchTool::registerSettingsWidget();
}

bool HelloWorld::toolOperations()
{
    if (!loadToDImg())
    {
        return false;
    }

    // Nothing to do.

    return (savefromDImg());
}

} // namespace DigikamBqmHelloWorldPlugin
