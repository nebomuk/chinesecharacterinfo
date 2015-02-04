#include "hanzisearch2.h"

#include <QFile>
#include <QTextStream>
#include <qstringlist.h>
#include <QtConcurrentRun>

/**
 * @brief deprecated, loads char dec data from decomp importable.txt
 */

HanziSearch2::HanziSearch2()
{
    QtConcurrent::run(this, &HanziSearch2::loadData);
}

QString HanziSearch2::getText(const QString &Hanzi)
{
    return Hanzi.length() > 0 ? hash.value(Hanzi.at(0)) : QString();
}

void HanziSearch2::loadData()
{
    QFile file(":decomp importable.txt");
    if(!file.open(QFile::ReadOnly))
    {
        qDebug("Error in HanziSearch::HanziSearch() : could not open file");
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");

        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList cells = line.split(QChar('\t'));
            if(cells.size() >2)
            hash.insert(cells.first().simplified(), cells.at(2).simplified());
        }
}
