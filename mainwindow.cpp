#include "mainwindow.hpp"

#include <QTextEdit>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  resize(800, 600);
  setWindowTitle("Print dialog");
  text_edit_ = new QTextEdit(this);
  text_edit_->setGeometry(0, 0, width(), height());
  // setCentralWidget(text_edit_);
}

void MainWindow::setText(const QString& text) { text_edit_->setText(text); }

MainWindow::~MainWindow() {}
