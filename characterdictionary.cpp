#include "characterdictionary.h"

CharacterDictionary::CharacterDictionary()
{
  fillDict();
}

QChar CharacterDictionary::getChar(uint8_t grayScale) const
{
  return m_dict.lower_bound(grayScale)->second;
}

void CharacterDictionary::fillDict()
{
  m_dict.insert({20,' '});
  m_dict.insert({40,'*'});
  m_dict.insert({60,'?'});
  m_dict.insert({80,'&'});
  m_dict.insert({100,'!'});
  m_dict.insert({120,'%'});
  m_dict.insert({140,'+'});
  m_dict.insert({160,'@'});
  m_dict.insert({180,'Y'});
  m_dict.insert({200,'B'});
  m_dict.insert({220,'S'});
  m_dict.insert({240,'T'});
  m_dict.insert({255,'M'});
}
