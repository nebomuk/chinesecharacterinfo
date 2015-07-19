#include "dictloader_edict.h"

#include <QFile>
#include <QRegExp>
#include <QTextStream>

DictLoaderEdict::DictLoaderEdict()
{

    int simpCharPos = 2; // the position of the character definition in a dic line, default: simplified


    int tradCharPos = 0; // trad chars are at the beginning


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

                QChar simpChar = line.at(simpCharPos);
                QChar tradChar = line.at(tradCharPos);
                addChar(&charDefSimp, simpChar, definition);
                addChar(&charDefTrad,tradChar,definition);

                if(!sTMap.contains(simpChar,tradChar))
                {
                    sTMap.insert(simpChar,tradChar);
                }
            }
    }
}

/*static*/ void DictLoaderEdict::addChar(QHash<QString, QString> *charDef, QString chineseChar, QString definition)
{

    if(charDef->contains(chineseChar))
    {
        QString val = charDef->value(chineseChar);
        charDef->insert(chineseChar,val + " " + definition); // append multiple definitions
    }
    else
    {
        charDef->insert(chineseChar,definition);
    }

}

QMultiHash<QChar, QChar> DictLoaderEdict::getSTMap() const
{
    return sTMap;
}

QChar DictLoaderEdict::s2T(QChar simpChar)
{
    if(getSTMap().contains(simpChar))  // contains  key (simp char)
    {
        return getSTMap().value(simpChar);
    }
    //else  if(getSTMap().values().contains(simpChar)) // not required

    // is already traditional or unkown
     // when unkown return at least any char, to avoid returning an empty string
    return simpChar;


}

QChar DictLoaderEdict::t2S(QChar tradChar)
{
    // exists at least oney key (simp char), return it
    if(!getSTMap().keys(tradChar).isEmpty())
    {
        return getSTMap().key(tradChar);
    }

    // either already simplified or unknown
    // when unkown return at least any char, to avoid returning an empty string
    return tradChar;
}



QHash<QString, QString> DictLoaderEdict::getDictT() const
{
    return charDefTrad;
}





