#ifndef CHARACTERDICTIONARY_H
#define CHARACTERDICTIONARY_H
#include <map>
#include <QChar>

class CharacterDictionary
{
public:
  CharacterDictionary();
  QChar getChar(uint8_t grayScale) const;
private:

  void fillDict();
  std::map<uint8_t,QChar> m_dict;
};

#endif // CHARACTERDICTIONARY_H
