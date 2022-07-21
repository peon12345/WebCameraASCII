#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <image2ASCIIConverter.h>
#include "webcamhandler.h"
#include <QTimer>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();



private slots:
   void showSym(const QStringList& list);

  void on_openFileButton_clicked();

  void on_startButton_clicked();

  void on_cameraButton_clicked();

private:
 const std::unique_ptr<ImageConverter> m_converter;
  WebcamHandler m_webCamHandler;
  QTimer m_timerWeb;
  Ui::MainWindow *ui;
  QFont m_font;


  // QWidget interface
protected:
  void resizeEvent(QResizeEvent *event) override;
private:
  QSize calculateSizeSym();
};
#endif // MAINWINDOW_H
