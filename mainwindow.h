#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <image2ASCIIConverter.h>
#include "webcamhandler.h"
#include <QTimer>
#include <memory>
#include <settingsform.h>
#include "texteffect.h"

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
  void on_openFileButton_clicked();
  void on_cameraButton_clicked();
  void on_settingsButton_clicked();

private:
  std::unique_ptr<ImageConverter> m_converter;
  std::unique_ptr<TextEffect> m_effect;
  WebcamHandler m_webCamHandler;
  QTimer m_timerWeb;
  Ui::MainWindow *ui;
  QFont m_font;

protected:
  void resizeEvent(QResizeEvent *event) override;
private:
  SettingsForm m_settingsForm;
  QSize calculateSizeSym();
  void setASCIIGradient();
  void connectSettings();
  void showSym(QStringList &&list);
};
#endif // MAINWINDOW_H
