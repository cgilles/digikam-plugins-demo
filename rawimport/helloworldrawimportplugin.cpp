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

#include <QVBoxLayout>
#include <QApplication>
#include <QPointer>
#include <QDebug>
#include <QByteArray>

namespace DigikamRawImportHelloWorldPlugin
{

HelloWorldRawImportPlugin::HelloWorldRawImportPlugin(QObject* const parent)
    : DPluginRawImport(parent),
      m_dcraw(nullptr),
      m_dlg(nullptr),
      m_history(nullptr),
      m_tempFile(nullptr)
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
    // TODO: Check dcraw availability ?
}

bool HelloWorldRawImportPlugin::run(const QString& filePath, const DRawDecoding& def)
{
    m_fileInfo = QFileInfo(filePath);
    m_props    = LoadingDescription(m_fileInfo.filePath(), LoadingDescription::ConvertForEditor);
    m_decoded  = DImg();
    m_tempFile = new QTemporaryFile();
    m_tempFile->open();

    m_dcraw    = new QProcess(this);
    m_dcraw->setProcessChannelMode(QProcess::MergedChannels);
    m_dcraw->setWorkingDirectory(m_fileInfo.path());
    m_dcraw->setStandardOutputFile(m_tempFile.fileName());

    m_dlg      = new QDialog(nullptr);
    m_dlg->setWindowTitle(QString::fromUtf8("Import RAW with dcraw"));

    QVBoxLayout* const vlay = new QVBoxLayout(m_dlg);
    m_history               = new DHistoryView(m_dlg);
    vlay->addWidget(m_history);
    m_dlg->setLayout(vlay);
    m_dlg->resize(600, 400);

    connect(m_dcraw, SIGNAL(started()),
            m_dlg, SLOT(open()));

    connect(m_dlg, SIGNAL(finished(int)),
            this, SLOT(slotDlgClosed()));

    connect(m_dcraw, SIGNAL(finished(int,QProcess::ExitStatus)),
            this, SLOT(slotProcessFinished(int,QProcess::ExitStatus)));

    connect(m_dcraw, SIGNAL(readyRead()),
            this, SLOT(slotProcessReadyRead()));

    m_fileInfo = QFileInfo(filePath);
    m_history->addEntry(QString::fromUtf8("Converting RAW image with dcraw..."), DHistoryView::StartingEntry);

    m_dcraw->start(QLatin1String("dcraw"), QStringList() << QLatin1String("-v") // Verbose
                                                         << QLatin1String("-4") // 8 bits per color per pixels
                                                         << QLatin1String("-T") // TIFF output
                                                         << QLatin1String("-c") // Piped output image
                                                         << filePath);

    return true;
}

void HelloWorldRawImportPlugin::slotProcessFinished(int code, QProcess::ExitStatus status)
{
    if (code < 0)
    {
        m_history->addEntry(QString::fromUtf8("Error to decode RAW image with dcraw!"), DHistoryView::ErrorEntry);
        m_history->addEntry( QString::fromUtf8("Close this dialog to load RAW image with native import tool"), DHistoryView::WarningEntry);
    }
    else
    {
        m_history->addEntry(QString::fromUtf8("Preparing to load pre-processed image..."), DHistoryView::ProgressEntry);

        m_props   = LoadingDescription(m_fileInfo.path() + QLatin1Char('/') + m_fileInfo.completeBaseName() + QLatin1String(".tiff"),
                                       LoadingDescription::ConvertForEditor);

        m_decoded = DImg(m_props.filePath);

        if (!m_decoded.isNull())
        {
            m_history->addEntry(QString::fromUtf8("Close this dialog to load pre-processed image in editor"), DHistoryView::SuccessEntry);
        }
        else
        {
            m_history->addEntry(QString::fromUtf8("Error to load decoded image!"), DHistoryView::ErrorEntry);
            m_history->addEntry(QString::fromUtf8("Close this dialog to load RAW image with native import tool"), DHistoryView::WarningEntry);
        }
    }
}

void HelloWorldRawImportPlugin::slotProcessReadyRead()
{
    QByteArray data   = m_dcraw->readAll();
    QStringList lines = QString::fromUtf8(data).split(QLatin1Char('\n'), QString::SkipEmptyParts);

    foreach (const QString& one, lines)
    {
        m_history->addEntry(one, DHistoryView::ProgressEntry);
    }
}

void HelloWorldRawImportPlugin::slotDlgClosed()
{
    qDebug() << "Closing Raw Import dialog...";

    if (m_decoded.isNull())
    {
        qDebug() << "Decoded image is null! Load with Native tool...";
        qDebug() << m_props.filePath;
        emit signalLoadRaw(m_props);
    }
    else
    {
        qDebug() << "Decoded image is not null...";
        qDebug() << m_props.filePath;
        emit signalDecodedImage(m_props, m_decoded);
    }
}

} // namespace DigikamRawImportHelloWorldPlugin
