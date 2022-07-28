#include "image2ASCIIConverter.h"
#include <QDebug>
#include <QElapsedTimer>

Image2ASCIIConverter::Image2ASCIIConverter()
{

}


QStringList Image2ASCIIConverter::convert(const cv::Mat mat) const
{

  cv::Mat matResized;
  cv::resize(mat,matResized,m_size);

  cv::Mat matGray;
  cv::cvtColor(matResized,matGray, cv::COLOR_BGR2GRAY);

  QStringList list;

  QString line;

  for(int i = 0; i < matGray.rows; ++i){

      line.clear();

      for( int j = 0; j < matGray.cols; ++j){

          line += m_dict.getChar(matGray.at<uchar>(i,j));
        }


      list.append(line);
    }

  return list;
}

void Image2ASCIIConverter::setASCIIGradient(const QString &gradient)
{
  m_dict.setASCIIGradient(gradient);
}








