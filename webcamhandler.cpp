#include "webcamhandler.h"
#include <chrono>
#include <thread>
#include <QDebug>

bool WebcamHandler::open()
{
  return m_cap.open(0);
}

void WebcamHandler::close()
{
 m_cap.release();
}

bool WebcamHandler::isOpened()
{
  return m_cap.isOpened();
}

WebcamHandler::WebcamHandler()
{

}

cv::Mat WebcamHandler::getFrame()
{
  cv::Mat frame;
  m_cap.read(frame);
  return frame;
}

