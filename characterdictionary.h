#ifndef CHARACTERDICTIONARY_H
#define CHARACTERDICTIONARY_H
#include <map>
#include <unordered_map>
#include <QChar>
#include <QString>

class CharacterDictionary
{
public:
  CharacterDictionary();
  QChar getChar(uint8_t grayScale) const;
  void setASCIIGradient(const QString& gradientStr);
private:
  QString m_gradientASCII;
  static constexpr int GRAY_SCALE = 255;
  void fillDict();


  std::array<QChar,GRAY_SCALE> m_dict;

 // std::map<uint8_t,QChar> m_dict;
};

#endif // CHARACTERDICTIONARY_H
