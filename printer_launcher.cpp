/* File: printer_launcher.cpp
Copyright (C) Basealt LLC,  2024
Author: Oleg Proskurin, <proskurinov@basealt.ru>

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "printer_launcher.hpp"

#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QFuture>
#include <QFutureWatcher>
#include <QMargins>
#include <QPrintDialog>
#include <QPrintEngine>
#include <QPrinter>
#include <QPrinterInfo>
#include <QProcess>
#include <QThread>
#include <QUrl>
#include <QtConcurrent>

namespace core {

PrinterLauncher::PrinterLauncher(QObject *parent)
    : QObject{parent}, m_window_{std::make_unique<MainWindow>(nullptr)} {
  connect(m_window_.get(), &MainWindow::printerSelected, this,
          &PrinterLauncher::performPrint);
}

/**
 * @brief Launch a native print dialog,print with cups
 * @param src_file - pdf file to print
 * @param page_count - total pages in file
 * @param landscape - true if orientation is landscape
 */
void PrinterLauncher::launch(const QStringList &src_files) {
  const QPrinterInfo default_printer = QPrinterInfo::defaultPrinter();
  if (!default_printer.isNull()) {
    m_window_->setDefaultPrinter(default_printer);
  }
  m_window_->show();
  src_files_ = src_files;
  watcher_ = std::make_unique<QFutureWatcher<ListPrinterInfos>>();
  connect(watcher_.get(), &QFutureWatcher<ListPrinterInfos>::finished, this,
          &PrinterLauncher::printersLookupFinished);

  const QFuture<ListPrinterInfos> fut_printers =
      QtConcurrent::run([]() { return QPrinterInfo::availablePrinters(); });
  watcher_->setFuture(fut_printers);
  m_window_->show();
}

void PrinterLauncher::printersLookupFinished() {
  m_window_->setPrinters(watcher_->result());
  m_window_->hideBusyIndicator();
  watcher_.reset();
}

void PrinterLauncher::performPrint(const QString &printer_name) {
  if (printer_name.isEmpty()) {
    return;
  }
  auto options = createPrintCommand(printer_name);
  auto *process = new QProcess();
  process->setProcessChannelMode(QProcess::ForwardedChannels);

  // finished
  connect(process, &QProcess::finished, [process, this] {
    process->deleteLater();
    m_window_->close();
  });

  //  error
  connect(process, &QProcess::errorOccurred,
          [process](QProcess::ProcessError err) {
            if (err == QProcess::FailedToStart) {
              qWarning() << "Cups executable failed to start:"
                         << QString(process->readAllStandardError());
            }
            process->close();
            process->deleteLater();
          });

  process->start(cups_executable_, options);
}

/// @details: https://www.cups.org/doc/options.html
/// @details: man lp-cups
QStringList PrinterLauncher::createPrintCommand(const QString &printer_name) {
  QStringList res;
  // printer name
  if (!printer_name.isEmpty()) {
    res.append("-d");
    res.append(printer_name);
  }
  // job name
  {
    const QString job_name = "print_pdf_" + printer_name;
    res.append("-t");
    res.append(job_name);
  }
  res.append(src_files_);
  return res;
}

}  // namespace core
