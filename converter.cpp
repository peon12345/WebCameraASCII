#include "converter.h"

QStringList ImageConverter::convert(const QImage img) const
{
  cv::Mat mat = QImageToCvMat(img);

  return  convert(mat);
}

void ImageConverter::resize(QSize size)
{
  m_size.height = size.height();
  m_size.width = size.width();
}

cv::Mat ImageConverter::QImageToCvMat( const QImage &inImage, bool inCloneImageData  ) const
{
  switch ( inImage.format() )
    {
    // 8-bit, 4 channel
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
      {
        cv::Mat  mat( inImage.height(), inImage.width(),
                      CV_8UC4,
                      const_cast<uchar*>(inImage.bits()),
                      static_cast<size_t>(inImage.bytesPerLine())
                      );

        return (inCloneImageData ? mat.clone() : mat);
      }

      // 8-bit, 3 channel
    case QImage::Format_RGB32:
    case QImage::Format_RGB888:
      {

        QImage   swapped = inImage;

        if ( inImage.format() == QImage::Format_RGB32 )
          {
            swapped = swapped.convertToFormat( QImage::Format_RGB888 );
          }

        swapped = swapped.rgbSwapped();

        return cv::Mat( swapped.height(), swapped.width(),
                        CV_8UC3,
                        const_cast<uchar*>(swapped.bits()),
                        static_cast<size_t>(swapped.bytesPerLine())
                        ).clone();
      }

      // 8-bit, 1 channel
    case QImage::Format_Indexed8:
      {
        cv::Mat  mat( inImage.height(), inImage.width(),
                      CV_8UC1,
                      const_cast<uchar*>(inImage.bits()),
                      static_cast<size_t>(inImage.bytesPerLine())
                      );

        return (inCloneImageData ? mat.clone() : mat);
      }

    }

  return cv::Mat();
}
