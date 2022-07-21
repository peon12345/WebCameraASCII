#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <QStringList>
#include <QColor>
#include <QFont>
#include <QDebug>
#include <QResizeEvent>


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , m_converter(new Image2ASCIIConverter()) , ui(new Ui::MainWindow),m_font("Lucida Console", 12)
{
  ui->setupUi(this);
  ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
  ui->textEdit->setStyleSheet("QTextEdit { background-color: rgb(0, 0, 0); }");
  ui->textEdit->setTextColor(QColor(255,255,255));


  ui->textEdit->setFont(m_font);

  connect(&m_timerWeb,&QTimer::timeout,this,[this]() {
   cv::Mat mat = m_webCamHandler.getFrame();
   showSym( m_converter->convert(mat) );
    });


}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::showSym(const QStringList &list)
{

  ui->textEdit->clear();

  for(const QString &str : list){
      ui->textEdit->append(str);
    }

}


void MainWindow::on_openFileButton_clicked()
{
  QString pathImage = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.jpg *.png");

  if(!pathImage.isEmpty()){
      ui->lineEditPath->setText(pathImage);
    }
}


void MainWindow::on_startButton_clicked()
{

  QImage img(ui->lineEditPath->text());

  if(!img.isNull()){
      QStringList list = m_converter->convert(img);
      showSym(list);
    }else{
      ui->textEdit->setText("Read error");
    }
}



void MainWindow::on_cameraButton_clicked()
{
  m_converter->resize(calculateSizeSym());
  m_timerWeb.start(50);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  Q_UNUSED(event);
  m_converter->resize(calculateSizeSym());
  //MainWindow::resizeEvent(event);
}

QSize MainWindow::calculateSizeSym()
{
 QFontMetrics metrics(m_font);
 int width = metrics.maxWidth() + metrics.maxWidth()/10;
 int height = metrics.height() + metrics.height()/10;

  return QSize(ui->textEdit->width()/width,ui->textEdit->height()/height);
}









