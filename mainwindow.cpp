#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <QStringList>
#include <QColor>
#include <QFont>
#include <QDebug>
#include <QResizeEvent>
#include <QElapsedTimer>
#include <QScrollBar>
#include "Effects.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent) ,
    ui(new Ui::MainWindow),m_font("Lucida Console", 10) , m_settingsForm (this)
{

  m_converter = std::make_unique<Image2ASCIIConverter>();

  ui->setupUi(this);
  ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
  ui->plainTextEdit->setStyleSheet("color: green; background-color: black;");

  ui->plainTextEdit->setFont(m_font);

  ui->lineEditGradient->setText(" *?&!%+@YBSTM");

  connect(&m_timerWeb,&QTimer::timeout,this,[this]() {

      cv::Mat mat = m_webCamHandler.getFrame();
      showSym( m_converter->convert(mat) );
    });


  m_effect = std::make_unique<MatrixEffect>("white");

}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::showSym( QStringList&& list)
{

  //if(m_effect){

      m_effect->applyEffect(list);


//    }else{


      ui->plainTextEdit->clear();

     for( QString &str : list){
         //str.replace(" " , "&nbsp;");
         ui->plainTextEdit->appendHtml(str);
       }

}


void MainWindow::on_openFileButton_clicked()
{
  QString pathImage = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.jpg *.png");

  if(!pathImage.isEmpty()){
      QImage img(pathImage);

      if(!img.isNull()){

          if(ui->comboBoxConvert->currentText() == "ASCII"){
              setASCIIGradient();
            }

          QStringList list = m_converter->convert(img);
          showSym(std::move(list));
        }else{
          ui->plainTextEdit->setPlainText("Read error");
        }
    }
}


void MainWindow::on_cameraButton_clicked()
{
  if(m_timerWeb.isActive()){
      m_webCamHandler.close();
      m_timerWeb.stop();
      ui->openFileButton->show();
      ui->cameraButton->setText("Start camera");

    }else{


      if(ui->comboBoxConvert->currentText() == "ASCII"){
          setASCIIGradient();
        }

      m_webCamHandler.open();
      m_converter->resize(calculateSizeSym());
      m_timerWeb.start(20);
      ui->openFileButton->hide();
      ui->cameraButton->setText("Stop");
    }

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

  return QSize(ui->plainTextEdit->width()/width,ui->plainTextEdit->height()/height);
}

void MainWindow::setASCIIGradient()
{
  auto ptr = m_converter.get();
  static_cast<Image2ASCIIConverter*>(ptr)->setASCIIGradient(ui->lineEditGradient->text());
}

void MainWindow::connectSettings()
{
  connect(&m_settingsForm,&SettingsForm::effectEnabled,[&settingsForm = m_settingsForm,&effect  =  m_effect](Effects e) {

      switch (e) {

        case Effects::MATRIX: {
            effect = std::make_unique<MatrixEffect>(std::get<1>(settingsForm.matrixEffectSettings()));
          }

        default:
          effect = std::make_unique<MatrixEffect>(std::get<1>(settingsForm.matrixEffectSettings()));
        }

    });


  connect(&m_settingsForm,&SettingsForm::colorChanged,[&effect  =  m_effect](Effects e, const QString& colorTag) {

      switch (e) {

        case Effects::MATRIX: {
            MatrixEffect* matEffect = dynamic_cast<MatrixEffect*>(effect.get());

            if(matEffect){
                matEffect->setColorTag(colorTag);
              }
          }


        default:
          MatrixEffect* matEffect = dynamic_cast<MatrixEffect*>(effect.get());

          if(matEffect){
              matEffect->setColorTag(colorTag);
            }
        }
    });




}



void MainWindow::on_settingsButton_clicked()
{
  m_settingsForm.show();
}

