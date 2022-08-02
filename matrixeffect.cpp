#include "matrixeffect.h"
#include <QRandomGenerator>
#include <QScrollBar>
#include <set>
#include <QDebug>

const QString  MatrixEffect::MatrixLine::SYMBOLS = "人七八九十入二三上下大女万土山千川子小口手五日六分中円月午今木父火以去兄広届乳念波拝板版非表府武並放法宝枚";

MatrixEffect::MatrixEffect(const QString &colorTag) : m_colorTag(colorTag)
{

}

void MatrixEffect::applyEffect(QWidget& widget , QStringList &list)
{

  //красится все
  //съезжает из за широкого символа

  static const  QString htmlTagBegin = "<font color=";
  static const  QString htmlTagEnd = "</font>";
  QString colorHtml = htmlTagBegin + m_colorTag + ">";
  int lenghtHtml  = colorHtml.length() ;
  static const QString htmlSpace = "&nbsp;";
  static const int htmlSpaceLength = htmlSpace.length();

  int lengthLine  = list.front().length();
  int blockLength = lengthLine  / BLOCK;
  int listSize = list.size();
  int tailSize = listSize/2;
  int minYInterval = listSize/3;

  // std::set<QPoint> linesHtml;
  std::vector<QPoint> linesHtml;
  linesHtml.reserve(listSize);

  std::vector<std::pair<int,int>> yOffsets;
  yOffsets.reserve(m_lines.size());

  for(int i = 0; i < blockLength; ++i){

      auto itRange = m_lines.equal_range(i);

      if(itRange.second == m_lines.end() ) {

          addMatLine(i , tailSize);

        }else{

          bool addLine = true;

          for(auto it = itRange.first ; it != itRange.second; ++it ) {

              it->second.step();

              if(it->second.currentPoint().y() > minYInterval) {
                  if(it->second.currentPoint().y() - it->second.tailLength() > listSize ){
                      m_lines.erase(it);
                      continue;
                    }else{
                      addLine = false;
                    }
                }

              const QPoint& point = it->second.currentPoint();
              const QString& matLine = it->second.line();

              for(int indLineY = 0; indLineY < it->second.length(); ++indLineY ) {

                  if( ( indLineY + point.y() ) < listSize){
                      QString& listLine = list[indLineY + point.y()];

                      // запишем все хтмл.
                      // для этого нужно смещение каждый раз делать.
                      // репласе в хтмл пробелы.

                      listLine[point.x()] = matLine.at(indLineY);

                      int offset = 0;
                      auto itOffset = std::find_if(yOffsets.begin() , yOffsets.end() , [indLineY] (const std::pair<int,int>& p ) {

                          return indLineY == p.second;

                        } );

                      if(itOffset != yOffsets.end()){

                          offset = itOffset->second;

                        }else{

                          int count = listLine.count(" ");
                          offset  = count * htmlSpaceLength;

                          listLine.replace(" " , htmlSpace);
                        }

                      insertHtml(listLine, );
                      listLine.insert(point.x() + offset ,colorHtml );
                      listLine.insert(point.x() + lenghtHtml + offset, htmlTagEnd);

                      offset += lenghtHtml + htmlTagEnd.length() ;

                      if(itOffset == yOffsets.end()){
                          yOffsets.push_back(std::make_pair(indLineY,offset));


                        }else{

                          itOffset->second = offset  + lenghtHtml + htmlTagEnd.length();

                        }


                      break;


                      if( (indLineY +1 ) ==  it->second.length()){
                          // linesHtml.insert(QPoint(point.x() , indLineY));
                          linesHtml.emplace_back(point.x() , indLineY);
                        }

                    }else{
                      break;
                    }

                }

            }

          if(addLine) {
              addMatLine(i,tailSize);
            }
        }
    }





  //  QPlainTextEdit* plainText;
  //  try {
  //    plainText = dynamic_cast<QPlainTextEdit*>(&widget);
  //  }
  //  catch (std::bad_cast exp) {
  //    return void();
  //  }

  //  plainText->clear();
  //  //<font color=red> Hello </font>

  //  for(int i = 0; i< listSize; ++i){

  //      auto it = std::find_if(linesHtml.begin() , linesHtml.end() ,  [i] (const QPoint& point) {

  //          return point.y() == i;

  //        } );


  //      if(it == linesHtml.end() ){
  //          qDebug() << "default plainText";
  //          plainText->appendPlainText(list.at(i));

  //        }
  //      else{
  //          const QString& line = list.at(i);
  //          colorHtml += line.at(it->x());
  //          colorHtml += htmlTagEnd;

  //          qDebug() << "append Html it->x y = " << it->x() << it->y();

  //          if(it->x() == 0){

  //             appendHtmlNoNL(plainText,colorHtml);
  //             appendPlainTextNoNL(plainText,line.mid(it->x() + 1,lengthLine - (it->x() + 1)));

  //            }
  //            else if(it->x() == lengthLine-1) {

  //             appendPlainTextNoNL(plainText,line.mid(0,it->x()) );
  //             appendHtmlNoNL(plainText,colorHtml);

  //            }else{

  //            appendPlainTextNoNL(plainText,line.mid(0,it->x()) );
  //            appendHtmlNoNL(plainText,colorHtml);
  //            appendPlainTextNoNL(plainText,line.mid(it->x() + 1,lengthLine - (it->x() + 1)));
  //            }





  //        }
  //    }


}

void MatrixEffect::setColorTag(const QString &colorTag)
{
  m_colorTag = colorTag;
}

void MatrixEffect::addMatLine(int block, int tailLength  )
{
  m_lines.insert(std::make_pair(block,MatrixLine(block * 10,tailLength)));
}

void MatrixEffect::insertHtml(QString &text, const QString &htmlLineBeg, const QString &htmlLineEnd)
{

}

void MatrixEffect::replaceSpace(QString &line)
{

}

void MatrixEffect::appendHtmlNoNL(QPlainTextEdit* textEdit,const QString &html)
{
  //  QScrollBar *p_scroll_bar = textEdit->verticalScrollBar();
  //  bool bool_at_bottom = (p_scroll_bar->value() == p_scroll_bar->maximum());


  QTextCursor text_cursor = QTextCursor(textEdit->document());
  text_cursor.movePosition(QTextCursor::End);
  text_cursor.insertHtml(html);


  text_cursor.endEditBlock();
  //  if (bool_at_bottom){
  //      p_scroll_bar->setValue(p_scroll_bar->maximum());
  //    }
}

void MatrixEffect::appendPlainTextNoNL(QPlainTextEdit *textEdit, const QString &text)
{
  QTextCursor text_cursor = QTextCursor(textEdit->document());
  text_cursor.movePosition(QTextCursor::End);
  text_cursor.insertText(text);

  text_cursor.endEditBlock();
}


MatrixEffect::MatrixLine::MatrixLine(int x, int len) : m_line{} , m_currentPoint(x,0) , m_len(len)
{
  for(int i = 0; i < m_len; ++i) {
      int  randomIndex = QRandomGenerator::global()->bounded(SYMBOLS_LEN);
      m_line += SYMBOLS[randomIndex];

    }
}

const QPoint &MatrixEffect::MatrixLine::currentPoint() const
{
  return m_currentPoint;
}

const QString &MatrixEffect::MatrixLine::line() const
{
  return m_line;
}

int MatrixEffect::MatrixLine::tailLength() const
{
  return m_len - 1;
}

int MatrixEffect::MatrixLine::length() const
{
  return m_len;
}

void MatrixEffect::MatrixLine::step()
{
  generateNewLine();
  m_currentPoint.setY(m_currentPoint.y() + 1);
}

void MatrixEffect::MatrixLine::generateNewLine()
{

  //меняем первый символ
  int randomIndex = QRandomGenerator::global()->bounded(SYMBOLS_LEN);
  m_line[0] = SYMBOLS[randomIndex];

  //меняем каждый третий символ у первой половины линии
  for(int i = 0; i < m_line.length() / 2; ++i) {

      if(i % 3 == 0 ){
          randomIndex = QRandomGenerator::global()->bounded(SYMBOLS_LEN);
          m_line[i] = SYMBOLS[randomIndex];
        }
    }

}
