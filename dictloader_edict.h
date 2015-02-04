#ifndef DICTLOADER_H
#define DICTLOADER_H

#include <QString>
#include <QHash>

// loads a hashtable from dics in the cc-cedict or handedict format

class DictLoaderEdict
{
public:
    DictLoaderEdict();
    QHash<QString,QString> getDict() const { return charDef;}

private:
    QHash<QString,QString> charDef;

};

#endif // DICTLOADER_H
