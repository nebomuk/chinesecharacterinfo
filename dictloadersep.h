#ifndef DICTLOADERSEP_H
#define DICTLOADERSEP_H

#include <QString>
#include <QHash>

// loads a hashtable from dics that are (tab) separator separated

class DictLoaderSep
{
public:
    DictLoaderSep(QString filePath, QString separator = "\t");
    QHash<QString,QString> getDict() const { return charDef;}

private:
    QHash<QString,QString> charDef;
    QString _separator;

};

#endif // DICTLOADER_H
