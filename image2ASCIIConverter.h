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
  CharacterDictionary m_dict;
};

#endif
