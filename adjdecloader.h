#include <QString>
#include <QHash>

#ifndef ADJACENTCHARACTERS_H
#define ADJACENTCHARACTERS_H

/**
 * @brief loads adjacent  or decompositions of characters  and their defintions
 *
 *     possible filenames ":AdjList.txt", ":decomp importable.txt"
 */

class AdjDecLoader
{
public:
    AdjDecLoader(const QString& fileName, QHash<QString,QString> charDef);

    QStringList getText(const QString& hanzi, bool colorIfSubAdj = false);

private:

private:
    void loadData();
    QHash<QString,QString> charDef; // characters -defnition
    QHash<QString,QStringList> charAdj; // characters -adjacent characters
    QString fileName;
};

#endif // ADJACENTCHARACTERS_H
