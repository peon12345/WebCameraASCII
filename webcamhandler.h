#ifndef WEBCAMHANDLER_H
#define WEBCAMHANDLER_H

#include <opencv2/opencv.hpp>
#include "converter.h"
#include <QObject>

class WebcamHandler : public QObject
{
  Q_OBJECT
public:
  WebcamHandler();
  cv::Mat getFrame();

private:
  cv::VideoCapture m_cap;
};

#endif // WEBCAMHANDLER_H
