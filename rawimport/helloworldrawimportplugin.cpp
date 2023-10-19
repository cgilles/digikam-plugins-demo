/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2019-09-09
 * Description : Hello World demo raw import plugin.
 *
 * Copyright (C) 2019-2023 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

// Local includes

#include "i18nutils.h"

namespace DigikamRawImportHelloWorldPlugin
{

HelloWorldRawImportPlugin::HelloWorldRawImportPlugin(QObject* const parent)
    : DPluginRawImport(parent),
      m_dcraw(nullptr),
      m_dlg(nullptr),
      m_history(nullptr),
      m_tempFile(nullptr)
{
    s_initI18nResource();
    s_loadI18n(name());
}

HelloWorldRawImportPlugin::~HelloWorldRawImportPlugin()
{
    s_cleanupI18nResource();
}

QString HelloWorldRawImportPlugin::name() const
{
    return tr("Demo Raw Import using dcraw");
}

QString HelloWorldRawImportPlugin::iid() const
{
    return QLatin1String(DPLUGIN_IID);
}

QIcon HelloWorldRawImportPlugin::icon() const
{
    return QIcon::fromTheme(QLatin1String("image-x-adobe-dng"));
}

QString HelloWorldRawImportPlugin::description() const
{
    return tr("A demo Hello World plugin");
}

QString HelloWorldRawImportPlugin::details() const
{
    return tr("<p>This Raw Import plugin is a simple demo using dcraw command line tool.</p>");
}

QList<DPluginAuthor> HelloWorldRawImportPlugin::authors() const
{
    return QList<DPluginAuthor>()
            << DPluginAuthor(QString::fromUtf8("Gilles Caulier"),
                             QString::fromUtf8("caulier dot gilles at gmail dot com"),
                             QString::fromUtf8("(C) 2019-2023"))
            ;
}

void HelloWorldRawImportPlugin::setup(QObject* const parent)
{
    // Nothing to do
}

bool HelloWorldRawImportPlugin::run(const QString& filePath, const DRawDecoding& def)
{
    m_fileInfo = QFileInfo(filePath);
    m_props    = LoadingDescription(m_fileInfo.filePath(), LoadingDescription::ConvertForEditor);
    m_decoded  = DImg();

    delete m_tempFile;

    m_tempFile = new QTemporaryFile();
    m_tempFile->open();

    m_dcraw    = new QProcess(this);
    m_dcraw->setProcessChannelMode(QProcess::MergedChannels);
    m_dcraw->setWorkingDirectory(m_fileInfo.path());
    m_dcraw->setStandardOutputFile(m_tempFile->fileName());

    connect(m_dcraw, SIGNAL(errorOccurred(QProcess::ProcessError)),
            this, SLOT(slotErrorOccurred(QProcess::ProcessError)));

    connect(m_dcraw, SIGNAL(finished(int,QProcess::ExitStatus)),
            this, SLOT(slotProcessFinished(int,QProcess::ExitStatus)));

    connect(m_dcraw, SIGNAL(readyRead()),
            this, SLOT(slotProcessReadyRead()));

    // --------

    delete m_dlg;

    m_dlg      = new QDialog(nullptr);
    m_dlg->setWindowTitle(tr("Import RAW with dcraw"));

    QVBoxLayout* const vlay = new QVBoxLayout(m_dlg);
    m_history               = new DHistoryView(m_dlg);
    vlay->addWidget(m_history);
    m_dlg->setLayout(vlay);
    m_dlg->resize(600, 400);

    connect(m_dlg, SIGNAL(finished(int)),
            this, SLOT(slotDlgClosed()));

    m_dlg->open();

    // --------

    m_fileInfo = QFileInfo(filePath);
    m_history->addEntry(tr("Converting RAW image with dcraw..."),                  DHistoryView::StartingEntry);
    m_history->addEntry(tr("Note: closing this dialog while processing "
                           "will load RAW image with native import tool"),         DHistoryView::ProgressEntry);
    m_history->addEntry(tr("Using temporary file %1").arg(m_tempFile->fileName()), DHistoryView::StartingEntry);

    m_dcraw->setProgram(QLatin1String("dcraw"));
    m_dcraw->setArguments(QStringList() << QLatin1String("-4") // 8 bits per color per pixels
                                        << QLatin1String("-T") // TIFF output
                                        << QLatin1String("-c") // Piped output image
                                        << filePath);

    m_history->addEntry(QString::fromUtf8("%1 %2").arg(m_dcraw->program())
                                                  .arg(m_dcraw->arguments().join(QLatin1Char(' '))),
                        DHistoryView::StartingEntry);

    m_dcraw->start();

    return true;
}

void HelloWorldRawImportPlugin::slotErrorOccurred(QProcess::ProcessError error)
{
    if (!m_dlg)
    {
        return;
    }

    m_history->addEntry(tr("Error to run dcraw! (code %1)").arg(error), DHistoryView::ErrorEntry);

    switch (error)
    {
        case QProcess::FailedToStart:
            m_history->addEntry(tr("Process has failed to start"), DHistoryView::ErrorEntry);
            break;

        case QProcess::Crashed:
            m_history->addEntry(tr("Process has crashed"), DHistoryView::ErrorEntry);
            break;

        case QProcess::Timedout:
            m_history->addEntry(tr("Process time-out"), DHistoryView::ErrorEntry);
            break;

        case QProcess::WriteError:
            m_history->addEntry(tr("Process write error"), DHistoryView::ErrorEntry);
            break;

        case QProcess::ReadError:
            m_history->addEntry(tr("Process read error"), DHistoryView::ErrorEntry);
            break;

        default:
            m_history->addEntry(tr("Process error unknown"), DHistoryView::ErrorEntry);
            break;
    }

    m_history->addEntry(tr("Close this dialog to load RAW image with native import tool"), DHistoryView::WarningEntry);
}

void HelloWorldRawImportPlugin::slotProcessFinished(int code, QProcess::ExitStatus status)
{
    if (!m_dlg)
    {
        return;
    }

    if (code < 0)
    {
        m_history->addEntry(tr("Error to decode RAW image with dcraw!"),                       DHistoryView::ErrorEntry);
        m_history->addEntry(tr("Close this dialog to load RAW image with native import tool"), DHistoryView::WarningEntry);
    }
    else
    {
        m_history->addEntry(tr("Preparing to load pre-processed image..."), DHistoryView::ProgressEntry);

        m_props   = LoadingDescription(m_tempFile->fileName(), LoadingDescription::ConvertForEditor);
        m_decoded = DImg(m_props.filePath);

        if (!m_decoded.isNull())
        {
            m_history->addEntry(tr("Close this dialog to load pre-processed image in editor"), DHistoryView::SuccessEntry);
        }
        else
        {
            m_history->addEntry(tr("Error to load decoded image!"),                                DHistoryView::ErrorEntry);
            m_history->addEntry(tr("Close this dialog to load RAW image with native import tool"), DHistoryView::WarningEntry);
        }
    }
}

void HelloWorldRawImportPlugin::slotProcessReadyRead()
{
    if (!m_dlg)
    {
        return;
    }

    QByteArray data   = m_dcraw->readAllStandardError();
    QStringList lines = QString::fromUtf8(data).split(QLatin1Char('\n'), QString::SkipEmptyParts);

    foreach (const QString& one, lines)
    {
        m_history->addEntry(one, DHistoryView::ProgressEntry);
    }
}

void HelloWorldRawImportPlugin::slotDlgClosed()
{
    qDebug() << "Closing Raw Import dialog...";

    delete m_dlg;
    m_dlg = nullptr;

    if (m_dcraw->state() == QProcess::Running)
    {
        m_dcraw->kill();
    }

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

    delete m_tempFile;
    m_tempFile = nullptr;
}

} // namespace DigikamRawImportHelloWorldPlugin
