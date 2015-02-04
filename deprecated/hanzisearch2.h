#ifndef HANZISEARCH2_H
#define HANZISEARCH2_H

#include <QHash>

/**
 * @brief deprecated, loads char dec data from decomp importable.txt
 */

class HanziSearch2
{
public:
    HanziSearch2();
    QString getText(const QString& Hanzi);

private:
     void loadData();
    QHash<QString,QString> hash;
};

#endif // HANZISEARCH2_H
