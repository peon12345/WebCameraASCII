#ifndef TEXTEFFECT_H
#define TEXTEFFECT_H
#include <QStringList>
#include <QWidget>

class TextEffect
{
public:
  TextEffect();
  virtual ~TextEffect() = default;
  virtual void applyEffect( QWidget& widget , QStringList& list) = 0;

};

#endif // TEXTEFFECT_H
