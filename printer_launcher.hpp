/* File: printer_launcher.hpp
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

#ifndef PRINTER_LAUNCHER_HPP
#define PRINTER_LAUNCHER_HPP

#include <QFutureWatcher>
#include <QObject>
#include <QPrinter>
#include <QProcess>
#include <QString>

#include "main_window.hpp"

namespace core {

constexpr const char *const kKeyO = "-o";

class PrinterLauncher : public QObject {
  using ListPrinterInfos = QList<QPrinterInfo>;

  Q_OBJECT

 public:
  explicit PrinterLauncher(QObject *parent = nullptr);

  /**
   * @brief Launch a native print dialog,print with cups
   * @param src_file - pdf file to print
   * @param page_count - total pages in file
   * @param landscape - true if orientation is landscape
   */
  Q_INVOKABLE void launch(const QStringList &src_files);

 signals:

 public slots:
  void performPrint(const QString &printer_name);

 private slots:
  void printersLookupFinished();

 private:
  /// @details: https://www.cups.org/doc/options.html
  /// @details: man lp-cups
  QStringList createPrintCommand(const QString &printer_name);

  const QString cups_executable_ = "lp-cups";

  std::unique_ptr<MainWindow> m_window_;
  std::unique_ptr<QFutureWatcher<ListPrinterInfos>> watcher_;
  QStringList src_files_;
  uint64_t counter_ = 0;
  QProcess *process_ = nullptr;
};

}  // namespace core

#endif  // PRINTER_LAUNCHER_HPP
