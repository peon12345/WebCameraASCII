#ifndef MATRIXEFFECT_H
#define MATRIXEFFECT_H

#include "texteffect.h"
#include <QPoint>
#include <QFont>
#include <unordered_map>
#include <QPlainTextEdit>

class MatrixEffect : public TextEffect
{
public:
  MatrixEffect() = default;
  MatrixEffect(const QString& colorTag);
  void applyEffect(QWidget& widget, QStringList& list) override;
  void setColorTag(const QString& colorTag);
private:

  class MatrixLine {

  public:
    MatrixLine(int x , int len);

    const QPoint& currentPoint() const;
    const QString& line() const;
    int tailLength() const;
    int length() const;
    void step();

  private:
    QString m_line;
    QPoint m_currentPoint;
    int m_len;

    static const QString SYMBOLS;
    static constexpr int SYMBOLS_LEN = 53;

  private:
    void generateNewLine();
  };

  static const int BLOCK = 10;
  static const int MAX_MATRIX_LINE_IN_BLOCK = 3;

  QString m_colorTag = "white";
  std::unordered_multimap<int,MatrixLine> m_lines;
  QFont m_font;
private:
  void addMatLine(int block , int tailLength);
  void appendHtmlNoNL(QPlainTextEdit* textEdit,const QString &html);
  void appendPlainTextNoNL(QPlainTextEdit* textEdit , const QString& text);
};

#endif // MATRIXEFFECT_H


