#include <QHash>

#ifndef HANZISEARCH_H
#define HANZISEARCH_H

/**
 * @brief loads the table with Remember the Hanzi data
 */

class HanziSearch
{
public:
    HanziSearch();
    QString getText(const QString& Hanzi);

private:
    void loadData();
    QHash<QString,QString> hash;
};

#endif // HANZISEARCH_H
