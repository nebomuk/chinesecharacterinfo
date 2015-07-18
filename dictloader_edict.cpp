#include "dictloader_edict.h"

#include <QFile>
#include <QRegExp>
#include <QTextStream>

DictLoaderEdict::DictLoaderEdict(Characters characters)
{

    int charDefPos = 2; // the position of the character definition in a dic line, default: simplified

    if(characters == Traditional)
    {
        charDefPos = 0; // trad chars are at the beginning
    }

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
                if(line.at(1) != QChar(' ')) // we are only interested in single char definitions
                    continue;

                QRegExp removePar(QRegExp::escape("(") + "[^)]*" + QRegExp::escape(")"));
                QString definition = line.right(line.size()-5).remove(removePar).remove("]").replace("/",", ").simplified();

                if(charDef.contains(line.at(charDefPos)))
                {
                    QString val = charDef[line.at(charDefPos)];
                    charDef.insert(line.at(charDefPos),val + " " + definition); // append multiple definitions
                }
                else
                {
                    charDef.insert(line.at(charDefPos),definition);
                }
            }
    }
}




