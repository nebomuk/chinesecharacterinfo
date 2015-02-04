#include "dictloader_edict.h"

#include <QFile>
#include <QRegExp>
#include <QTextStream>

DictLoaderEdict::DictLoaderEdict()
{
    // file 12mb to big for embedding into resource?
    {
        QFile file(":cedict_ts.u8");
        if(!file.open(QFile::ReadOnly))
        {
            qDebug("Error in AdjacentCharacters::loadData() : could not open file");
        }
        QTextStream in(&file);
        in.setCodec("UTF-8");

        //鬧 闹 [nao4] /lärmend, auslassen, an etw. leiden (u.E.) (V)/
            while (!in.atEnd())
            {
                // for other uses can also be split with regexp for [ ] chars and QString::split

                QString line = in.readLine();
                if(line.at(1) != QChar(' '))
                    continue;

                QRegExp removePar(QRegExp::escape("(") + "[^)]*" + QRegExp::escape(")"));
                QString definition = line.right(line.size()-5).remove(removePar).remove("]").replace("/",", ").simplified();

                if(charDef.contains(line.at(2)))
                {
                    QString val = charDef[line.at(2)];
                    charDef.insert(line.at(2),val + " " + definition); // append multiple definitions
                }
                else
                {
                    charDef.insert(line.at(2),definition);
                }
            }
    }
}




