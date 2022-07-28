#include "characterdictionary.h"

//"$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^`'. ";
//" *?&!%+@YBSTM";


CharacterDictionary::CharacterDictionary()
{

}

QChar CharacterDictionary::getChar(uint8_t grayScale) const
{
  return m_dict[grayScale];
}

void CharacterDictionary::setASCIIGradient(const QString &gradientStr)
{
  m_gradientASCII = gradientStr;
  fillDict();
}

void CharacterDictionary::fillDict()
{
  float interval = (float)GRAY_SCALE /  (float)m_gradientASCII.length();

  int intervalInt = interval;
  float intervalEnd = interval - intervalInt;
  float currentEnd = 0.0;
  int index = 0;
  int indexASCII = 0;

  for(float i = 0; i < GRAY_SCALE; i += interval ){

      currentEnd += intervalEnd;

      if(currentEnd >= 1 ){
        m_dict[index] = m_gradientASCII.at(indexASCII);
        index++;
        currentEnd -= 1;
        }

      for(int g = 0; g< intervalInt; ++g){
        m_dict[index] = m_gradientASCII.at(indexASCII);
        index++;
        }
      indexASCII++;
    }


}






