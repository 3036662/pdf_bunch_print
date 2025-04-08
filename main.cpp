#include <QApplication>
#include <QPrinterInfo>
#include <QWidget>

#include "printer_launcher.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QStringList args = QApplication::arguments();
  qWarning() << args.join("\n");
  args.removeFirst();
  core::PrinterLauncher printer;
  printer.print(args, 0, false);

  return a.exec();
}
