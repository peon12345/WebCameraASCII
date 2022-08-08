#include "matrixeffect.h"
#include <QRandomGenerator>
#include <QScrollBar>
#include <set>
#include <QDebug>

const QString  MatrixEffect::MatrixLine::SYMBOLS = "人七八九十入二三上下大女万土山千川子小口手五日六分中円月午今木父火以去兄広届乳念波拝板版非表府武並放法宝枚";
const  QString MatrixEffect::HTML_TAG_BEGIN = "<font color=";
const  QString MatrixEffect::HTML_TAG_END = "</font>";



MatrixEffect::MatrixEffect(const QString &colorTag)
{
  m_settingData.setColor(colorTag);
}

void MatrixEffect::applyEffect(QStringList &list)
{
  QString colorHtml = HTML_TAG_BEGIN + m_settingData.colorTag() + ">";

  QSize listSize;
  listSize.setHeight( list.size());

  if(listSize.height() != m_settingData.sizeList().height()){
      listSize.setWidth(list.front().length());
      m_settingData.setSizeList(listSize);

      m_lines.rehash(m_settingData.blockLength());
    }


  for(int i = 0; i <  m_settingData.blockLength(); ++i){

      auto itRange = m_lines.equal_range(i);

      if(itRange.second == m_lines.end() && itRange.first ==  m_lines.end()) {
          qDebug() << "added";
          addMatLine(i , m_settingData.tailSize());

        }else{

          bool addLine = true;

          for(auto it = itRange.first ; it != itRange.second; ++it ) {

              it->second.step();

//              qDebug() << "if";
//              qDebug() << it->second.currentPoint().y() << ">" << m_settingData.minYInterval();
//              qDebug() << (it->second.currentPoint().y() - it->second.tailLength()) << ">" <<  m_settingData.sizeList().height();
              if(it->second.currentPoint().y() > m_settingData.minYInterval()) {
                  if(it->second.currentPoint().y() - it->second.tailLength() > m_settingData.sizeList().height() ){

                      qDebug() << "erased" << it->second.currentPoint().y();
                        m_lines.erase(it);
                      continue;
                    }else{
                      addLine = false;
                    }
                }

              const QPoint& point = it->second.currentPoint();
              const QString& matLine = it->second.line();

             for(int indLineY = 0; indLineY < it->second.length(); ++indLineY ) {
               if( (point.y() - indLineY ) < m_settingData.sizeList().height() && (point.y() - indLineY ) >= 0){
               QString& listLine = list[point.y() - indLineY];

                  int index =  indexNotHtml(listLine,point.x(),colorHtml,HTML_TAG_END);
                  listLine[index] = matLine.at(indLineY);

                  if(indLineY < 3){
                  insertHtml(listLine , index , colorHtml, HTML_TAG_END );
                    }

                  addLine = false;
                 }
               }

               qDebug() << m_lines.size();

              //              for(int indLineY = 0; indLineY < it->second.length(); ++indLineY ) {

              //                  if( ( indLineY + point.y() ) < m_settingData.sizeList().height()){
              //                      QString& listLine = list[indLineY + point.y()];

              //                      int index =  indexNotHtml(listLine,point.x(),colorHtml,HTML_TAG_END);
              //                      listLine[index] = matLine.at(indLineY);

              //                      if(indLineY ==0){
              //                      insertHtml(listLine , index , colorHtml, HTML_TAG_END );
              //                        }

              //                      break;


              //                    }else{
              //                      break;
              //                    }

              //                }

            }

          if(addLine) {
              qDebug() << "added 2";
              addMatLine(i,m_settingData.tailSize());
            }
        }
    }


  replaceSpace(list);

}

void MatrixEffect::setColorTag(const QString &colorTag)
{
  m_settingData.setColor(colorTag);
}

void MatrixEffect::addMatLine(int block, int tailLength  )
{
  m_lines.insert(std::make_pair(block,MatrixLine(block * 10,tailLength)));
}

int MatrixEffect::indexNotHtml(const QString &text, int index , const QString &htmlLineBeg, const QString &htmlLineEnd)
{
  int lengthHtmlBeg = htmlLineBeg.length();
  int lengthHtmlEnd = htmlLineEnd.length();

  int posHtml = 0;
  int counter = 0;

  int currentIndex =0;

  do{

      posHtml = text.indexOf(htmlLineBeg,posHtml);

      if(posHtml != -1 ){


          currentIndex = posHtml - ( counter * ( lengthHtmlBeg + lengthHtmlEnd ) );


          if(currentIndex < index){
              counter++;
            }else{
              //            posHtml++;
              //            posHtml = text.indexOf(htmlLineBeg,posHtml);
              break;

            }
        }else{

          break;
        }

      posHtml++;
      //взять след начало
      // начало и конец
      // если коунтер + индекс в ренже начало и конец
      //коунтер + индекс
      //коунтер +  (конец  - коунтер) + (коунтер - начало)

    }while(posHtml > 0 && currentIndex < index);

  int begHtmlPos = 0;
  int endHtmlPos = 0;

  if(posHtml != -1){

      begHtmlPos = posHtml;
      endHtmlPos = posHtml +   lengthHtmlBeg + lengthHtmlEnd;
    }


  counter *=  lengthHtmlBeg + lengthHtmlEnd;

  int newIndex = index + counter;

  if(begHtmlPos != 0 && endHtmlPos != 0){

      while( newIndex >= begHtmlPos && newIndex <= endHtmlPos ){

          newIndex = newIndex + (endHtmlPos - newIndex) + (newIndex - begHtmlPos) ;

          posHtml++;
          posHtml = text.indexOf(htmlLineBeg,posHtml);

          if(posHtml != -1) {

              begHtmlPos = posHtml;
              endHtmlPos = posHtml +   lengthHtmlBeg + lengthHtmlEnd;

            }else{

              break;

            }

        }
    }

  return  newIndex;


}

void MatrixEffect::insertHtml(QString &text, int posInsert ,  const QString &htmlLineBeg, const QString &htmlLineEnd)
{
  int lengthHtml = htmlLineBeg.length() + 1;

  text.insert(posInsert ,htmlLineBeg );
  text.insert(posInsert + lengthHtml , htmlLineEnd);
}

void MatrixEffect::replaceSpace(QStringList &list)
{
  static const QString htmlSpace = "&nbsp;";

  for(int i = 0; i < list.size(); ++i){

      QString& line =  list[i];

      line.replace(" " , "&nbsp;");
      line.replace("<font&nbsp;color=","<font color=");
    }

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


  for(int i = 0; i < m_line.length() ; ++i) {

      if(i % 2 == 0 ){
          randomIndex = QRandomGenerator::global()->bounded(SYMBOLS_LEN);
          m_line[i] = SYMBOLS[randomIndex];
        }
    }

}

void MatrixEffect::SettingData::setSizeList(const QSize &listSize)
{

  m_listSize = listSize;

  m_lengthLine  = listSize.width();
  m_blockLength = m_lengthLine  / BLOCK;

  m_tailSize = listSize.height()/2;
  m_minYInterval = listSize.height()/3;


}

void MatrixEffect::SettingData::setColor(const QString &colorTag)
{


  m_colorTag = colorTag;

}

const QString &MatrixEffect::SettingData::colorTag() const
{
  return m_colorTag;
}

const QSize &MatrixEffect::SettingData::sizeList() const
{
  return m_listSize;
}

int MatrixEffect::SettingData::blockLength() const
{
  return m_blockLength;
}

int MatrixEffect::SettingData::lengthLine() const
{
  return m_lengthLine;
}

int MatrixEffect::SettingData::tailSize() const
{
  return m_tailSize;
}

int MatrixEffect::SettingData::minYInterval() const
{
  return m_minYInterval;
}

const QFont& MatrixEffect::SettingData::font() const
{
  return m_font;
}



