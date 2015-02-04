#include "dictloadersep.h"

#include <QFile>
#include <QRegExp>
#include <QTextStream>

DictLoaderSep::DictLoaderSep(QString filePath, QString separator)
{
    // file 12mb to big for embedding into resource?
    {
        _separator = separator;
        QFile file(filePath);
        if(!file.open(QFile::ReadOnly))
        {
            qDebug("Error in AdjacentCharacters::loadData() : could not open file");
        }
        QTextStream in(&file);
        in.setCodec("UTF-8");

            while (!in.atEnd())
            {
                QString line = in.readLine();
                if(line.at(1) != QChar('\t'))
                    continue;

                QRegExp removePar(QRegExp::escape("(") + "[^)]*" + QRegExp::escape(")"));
                QString definition = line.section("\t",2).remove(removePar).remove("]").remove("/").replace("\t"," ").simplified();

                QString simpleChar = line.section("\t",1,1);
                QString pinyin = line.section("\t",2,2);
                if(charDef.contains(simpleChar))
                {
                    QString val = charDef[simpleChar];
                    charDef.insert(simpleChar,val + ", " + definition); // append multiple definitions
                }
                else
                {
                    charDef.insert(simpleChar,definition);
                }
            }
    }
}




