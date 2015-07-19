#ifndef DICTLOADER_H
#define DICTLOADER_H

#include <QString>
#include <QHash>

// loads a hashtable from dics in the cc-cedict or handedict format

class DictLoaderEdict
{

public:

    // loads the dic from the resources, keys can be traditional or simplified
    DictLoaderEdict();

    QHash<QString,QString> getDict() const { return charDefSimp;} // hash map containining the char as a key, and the definition as value
    QHash<QString, QString> getDictT() const; // traditional of the above


    QMultiHash<QChar, QChar> getSTMap() const; // mapping between simplified and traditional chars

    QChar s2T(QChar simpChar); // attemps to convert the simplified char to a traditional variant
    QChar t2S(QChar tradChar); // as above, but the other way round


private:
    QHash<QString,QString> charDefSimp; // simplified definitions
    QHash<QString, QString> charDefTrad; // traditional definitions
    QMultiHash<QChar, QChar> sTMap;


    static void addChar(QHash<QString, QString> * charDefSimp, QString chineseChar, QString definition);
};

#endif // DICTLOADER_H
