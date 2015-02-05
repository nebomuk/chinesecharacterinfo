#ifndef CONVERTPINYIN_H
#define CONVERTPINYIN_H

#include <QString>

/**
 * @brief The ConvertPinyin class convertes pinyin number formatted text  to accented pinyin
 * based on
 * http://stackoverflow.com/questions/6159239/any-libraries-to-convert-number-pinyin-to-pinyin-with-tone-markings
 */

class ConvertPinyin
{
public:
    ConvertPinyin();
    static QString ConvertNumericalPinYinToAccented(QString input);
};

#endif // CONVERTPINYIN_H
