#include "webcamhandler.h"
#include <chrono>
#include <thread>
#include <QDebug>

WebcamHandler::WebcamHandler() : m_cap(0)
{

}

cv::Mat WebcamHandler::getFrame()
{
  cv::Mat frame;
  m_cap.read(frame);
  return frame;
}

