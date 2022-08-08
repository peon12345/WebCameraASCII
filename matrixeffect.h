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
  void applyEffect(QStringList& list) override;
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


  class SettingData {

  public:

    void setColor(const QString& colorTag);
    const QString& colorTag() const;

    const QSize& sizeList() const;
    void setSizeList(const QSize& listSize);
    int blockLength() const;
    int lengthLine() const;
    int tailSize() const;
    int minYInterval() const;
    const QFont &font() const;

  private:
    QString m_colorTag = "white";
    int m_lengthLine;
    int m_blockLength;
    QSize m_listSize = QSize(0,0);
    int m_tailSize;
    int m_minYInterval;
    QFont m_font;

  } m_settingData;

  static const int BLOCK = 10;
  static const int MAX_MATRIX_LINE_IN_BLOCK = 3;
  static const  QString HTML_TAG_BEGIN;
  static const  QString HTML_TAG_END;

  std::unordered_multimap<int,MatrixLine> m_lines;
private:
  void addMatLine(int block , int tailLength);

  int indexNotHtml(const QString& text,int index,const QString& htmlLineBeg,const QString& htmlLineEnd);
  void insertHtml(QString& text , int posInsert, const QString& htmlLineBeg , const QString& htmlLineEnd );
  void replaceSpace(QStringList& list);
//  void appendHtmlNoNL(QPlainTextEdit* textEdit,const QString &html);
//  void appendPlainTextNoNL(QPlainTextEdit* textEdit , const QString& text);
};

#endif // MATRIXEFFECT_H


