#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QDialog>
#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  void setText(const QString& text);

 private:
  // QTextEdit* text_edit_;
};
#endif  // MAINWINDOW_HPP
