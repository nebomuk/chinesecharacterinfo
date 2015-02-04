#include "hanzisearch.h"

#include <QFile>
#include <QTextStream>
#include <QtConcurrentRun>
#include <qstringlist.h>

HanziSearch::HanziSearch()
{
    QtConcurrent::run(this, &HanziSearch::loadData);
}

QString HanziSearch::getText(const QString &Hanzi)
{
    return Hanzi.length() > 0 ? hash.value(Hanzi.at(0)) : QString();
}

void HanziSearch::loadData()
{
    QFile file(":hanzitable.csv");
    if(!file.open(QFile::ReadOnly))
    {
        qDebug("Error in HanziSearch::HanziSearch() : could not open file");
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");

        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList cells = line.split(QChar(';'));
            QString phrase;
            for(int i = 2; i< cells.size(); ++i)
            {
                phrase += cells.at(i);
            }
            hash.insert(cells.first().simplified(), cells.at(1).simplified() + ": " + phrase.simplified());// do not use cells.last() because of some leading ;; characters in some rows
        }
}
