#include "image2ASCIIConverter.h"
#include <QDebug>


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

  for(int i = 0; i < matGray.rows; ++i){

      list.append(convertMatRow(matGray,i));
    }

  return list;
}

QString Image2ASCIIConverter::convertMatRow(cv::Mat mat,int rowInd) const
{

 QString line;

  for( int j = 0; j < mat.cols; ++j){

      line += m_dict.getChar(mat.at<uchar>(rowInd,j));
    }

  return line;
}







