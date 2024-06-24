/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2019-09-09
 * Description : Hello World demo raw import plugin.
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

#pragma once

// Qt includes

#include <QProcess>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QDialog>

// Digikam includes

#include "dpluginrawimport.h"
#include "dhistoryview.h"
#include "dimg.h"
#include "loadingdescription.h"

#define DPLUGIN_IID "org.kde.digikam.plugin.rawimport.HelloWorld"

using namespace Digikam;

namespace DigikamRawImportHelloWorldPlugin
{

class HelloWorldRawImportPlugin : public DPluginRawImport
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DPLUGIN_IID)
    Q_INTERFACES(Digikam::DPluginRawImport)

public:

    explicit HelloWorldRawImportPlugin(QObject* const parent = nullptr);
    ~HelloWorldRawImportPlugin();

    QString name()                 const override;
    QString iid()                  const override;
    QIcon   icon()                 const override;
    QString details()              const override;
    QString description()          const override;
    QList<DPluginAuthor> authors() const override;

    void setup(QObject* const)           override;

    bool run(const QString& filePath, const DRawDecoding& def);

private Q_SLOTS:

    void slotErrorOccurred(QProcess::ProcessError);
    void slotProcessFinished(int, QProcess::ExitStatus);
    void slotProcessReadyRead();
    void slotDlgClosed();

private:

    QProcess*          m_dcraw      = nullptr;
    QDialog*           m_dlg        = nullptr;
    DHistoryView*      m_history    = nullptr;
    DImg               m_decoded;
    LoadingDescription m_props;
    QFileInfo          m_fileInfo;
    QTemporaryFile*    m_tempFile   = nullptr;
};

} // namespace DigikamRawImportHelloWorldPlugin
