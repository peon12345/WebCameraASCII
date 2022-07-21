#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H
#include <QStringList>
#include <QString>
#include <QPixmap>

#include <opencv2/core/mat.hpp>

class ImageConverter {

public:
  virtual QStringList convert(const QImage img )const;
  virtual QStringList convert(const cv::Mat mat) const =0;
  void resize(QSize size);
  virtual ~ImageConverter() = default;
protected:
  virtual cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true ) const;
  cv::Size m_size = {100,100};

};


#endif // IMAGECONVERTER_H
