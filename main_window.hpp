#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPrinterInfo>
#include <QTextEdit>

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override = default;

  void setPrinters(const QList<QPrinterInfo>& printers);
  void setDefaultPrinter(const QPrinterInfo& printer);
  void hideBusyIndicator();

 signals:
  void printerSelected(QString printer_name);

 private slots:
  void printButtonClicked();

 private:
  QComboBox* combo_box_ = nullptr;
  QLabel* loading_label_gif_ = nullptr;
  QMovie* busy_indicator_ = nullptr;
  QLabel* loading_label_text_ = nullptr;
  QPushButton* button_ = nullptr;
};
#endif  // MAINWINDOW_HPP
