#ifndef DICTLOADER_H
#define DICTLOADER_H

#include <QString>
#include <QHash>

// loads a hashtable from dics in the cc-cedict or handedict format

class DictLoaderEdict
{

public:

    enum Characters
    {
        Traditional,
        Simplified
    };

    // loads the dic from the resources, keys can be traditional or simplified
    DictLoaderEdict(Characters characters = Simplified);

    QHash<QString,QString> getDict() const { return charDef;} // hash map containining the char as a key, and the definition as value

private:
    QHash<QString,QString> charDef;

};

#endif // DICTLOADER_H
