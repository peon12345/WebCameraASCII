#ifndef IMAGE2ASCIICONVERTER
#define IMAGE2ASCIICONVERTER


#include <opencv2/opencv.hpp>

#include "converter.h"
#include "characterdictionary.h"

class Image2ASCIIConverter final: public ImageConverter
{
public:
  Image2ASCIIConverter();
  QStringList convert(const cv::Mat mat) const override;
private:
  QString convertMatRow(const cv::Mat mat,int rowInd) const;
private:
  CharacterDictionary m_dict;
};

#endif
