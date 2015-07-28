#include "adjdecloader.h"

#include <QFile>
#include <QtConcurrentRun>
#include <qstringlist.h>
#include <QRegExp>
#include "charfreq.h"
#include "color.h"


void AdjDecLoader::loadData()
{
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly))
        {
            qDebug("Error in AdjacentCharacters::loadData() : could not open file");
            return;
        }
        QTextStream in(&file);
        in.setCodec("UTF-8");
            while (!in.atEnd())
            {

                QString line = in.readLine();
                line = line.remove(QChar(','));
                QStringList chars;
                for(int i = 0; i< line.length(); ++i)
                    chars << line.at(i);

                if(chars.size() <2)
                    continue;

                QString  first = chars.at(0);
                chars.removeFirst();
                charAdj.insert(first,chars);
            }
}

AdjDecLoader::AdjDecLoader(const QString& fileName, QHash<QString, QString> charDef, Characters characters)
{
    this->fileName = fileName;
    this->charDef = charDef;
    this->characters = characters;
    QtConcurrent::run(this, &AdjDecLoader::loadData);
}

QStringList AdjDecLoader::getText(const QString &hanzi, bool colorIfSubAdj)
{
    if(hanzi.size() == 0)
        return QStringList();

    QStringList texts;
    QStringList adjs = charAdj[hanzi.at(0)];


    if(characters == Simplified)
    {
        qSort(adjs.begin(),adjs.end(),CharFreq::moreFrequent);
    }
    else
    {
        qSort(adjs.begin(),adjs.end(),CharFreq::moreFrequentT);
    }

    QStringListIterator it(adjs);
    while(it.hasNext())
    {
        QString adj = it.next();

        if(!charDef.contains(adj)) // no definition
        {
            texts += "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;  \">"
                     "<span style=\" background-color:#f0f0f0;\"><span style=\" font-size:16pt;\">" + adj + "</span></span></p>";
            continue;
        }

        bool hasAdj = charAdj.contains(adj); // check if this adjacent char has any chars that are adjacent to it


        QString pinyin = charDef[adj].section(" ",0,0);


        if(hasAdj && colorIfSubAdj) // make background gray
        {

            texts += "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;  \">"
                "<span style=\" background-color:#f0f0f0;\"><span style=\" font-size:16pt;\">" + Color::addColorSpan(adj,pinyin) + "</span></span>" + charDef[adj] + "</p>";
        }
        else
        {
            texts += "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; vertical-align:top; \">"
                    "<span style=\" font-size:16pt;\">" + Color::addColorSpan(adj,pinyin) + "</span> " + charDef[adj] + "</p>";
        }

    }
    return texts;
}
