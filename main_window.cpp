#include "main_window.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QTextEdit>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      combo_box_(new QComboBox()),
      loading_label_gif_(new QLabel()),
      busy_indicator_(
          new QMovie(":/radar.gif", QByteArray(), loading_label_gif_)),
      loading_label_text_(new QLabel()),
      button_(new QPushButton(tr("Print"))) {
  setFixedSize(500, 100);
  setWindowTitle(tr("Print PDF"));
  auto* w_main = new QWidget(this);
  auto* v_layout = new QVBoxLayout();
  setCentralWidget(w_main);
  w_main->setLayout(v_layout);

  // combo and button
  combo_box_->setDuplicatesEnabled(false);
  connect(button_, &QPushButton::clicked, this,
          &MainWindow::printButtonClicked);
  auto* combo_hlayout = new QHBoxLayout();
  combo_hlayout->addWidget(combo_box_, 6);
  combo_hlayout->addWidget(button_, 3);

  // busy indicator (gif)
  auto* text_hlayout = new QHBoxLayout();
  text_hlayout->addSpacing(10);
  text_hlayout->addStretch();
  loading_label_gif_->setMaximumSize(32, 32);
  loading_label_gif_->setMovie(busy_indicator_);
  busy_indicator_->start();
  text_hlayout->addWidget(loading_label_gif_);
  // text
  loading_label_text_->setText(tr("Searching for printers"));
  text_hlayout->addWidget(loading_label_text_);
  text_hlayout->addStretch();
  v_layout->addLayout(text_hlayout);
  v_layout->addLayout(combo_hlayout);
}

void MainWindow::setDefaultPrinter(const QPrinterInfo& printer) {
  combo_box_->addItem(printer.printerName());
  combo_box_->setCurrentText(printer.printerName());
}

void MainWindow::setPrinters(const QList<QPrinterInfo>& printers) {
  int default_index_printer = -1;
  int curr_index = 0;
  std::for_each(
      printers.cbegin(), printers.cend(),
      [this, &curr_index, &default_index_printer](const QPrinterInfo& printer) {
        combo_box_->addItem(printer.printerName());
        ++curr_index;
      });
  if (default_index_printer >= 0) {
    combo_box_->setCurrentIndex(default_index_printer);
  }
}

void MainWindow::hideBusyIndicator() {
  busy_indicator_->stop();
  loading_label_gif_->hide();
  loading_label_text_->hide();
}

void MainWindow::printButtonClicked() {
  combo_box_->setEnabled(false);
  button_->setEnabled(false);
  emit printerSelected(combo_box_->currentText());
}
