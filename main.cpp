#include <QApplication>
#include <QDirIterator>
#include <QTranslator>

#include "printer_launcher.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  // translator
  QTranslator translator;
  const QString locale = QLocale::system().name();
  const QString translation_path = ":/translations/" + locale + ".qm";
  if (!translator.load(translation_path)) {
    qWarning("Load translations failed");
  } else {
    QApplication::installTranslator(&translator);
  }

  QStringList args = QApplication::arguments();
  // qWarning() << args.join("\n");
  args.removeFirst();
  core::PrinterLauncher printer;
  printer.print(args, 0, false);
  return a.exec();
}
