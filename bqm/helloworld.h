/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2019-09-01
 * Description : Hello World batch tool.
 *
 * Copyright (C) 2019-2023 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_BQM_HELLO_WORLD_H
#define DIGIKAM_BQM_HELLO_WORLD_H

// Local includes

#include "batchtool.h"

using namespace Digikam;

namespace DigikamBqmHelloWorldPlugin
{

class HelloWorld : public BatchTool
{
    Q_OBJECT

public:

    explicit HelloWorld(QObject* const parent = nullptr);
    ~HelloWorld();

    BatchToolSettings defaultSettings()
    {
        return BatchToolSettings();
    };

    BatchTool* clone(QObject* const parent=nullptr) const { return new HelloWorld(parent); };

    void registerSettingsWidget();

private:

    bool toolOperations();

private Q_SLOTS:

    void slotAssignSettings2Widget() {};
    void slotSettingsChanged()       {};
};

} // namespace DigikamBqmHelloWorldPlugin

#endif // DIGIKAM_BQM_HELO_WORLD_H
