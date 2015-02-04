#include <QString>

#ifndef COLORS_H
#define COLORS_H

//pleco style colors

namespace Color{

QString addColorSpan(const QString& hanzi, const QString& pinyin);

const QString spanRed = "<span style=\"color:#DD0000\">";
const QString spanGreen = "<span style=\"color:#00A600\">";
const QString spanPurple = "<span style=\"color:#CA2CFF\">";
const QString spanBlue = "<span style=\"color:#0000FF\">";

const QString red = "#DD0000";
const QString green = "#00A600";
const QString purple = "#CA2CFF";
const QString blue  = "#0000FF";

QString addColorSpan(const QString& hanzi, const QString& pinyin)
{
    if(pinyin.contains(" ")) // if pinyin contains spaces, there are multiple pronounciations with possibly different tones
        return hanzi;
    else if(pinyin.contains("1"))
        return spanRed + hanzi + "</span>";
    else if(pinyin.contains("2"))
        return spanGreen + hanzi + "</span>";
    else if(pinyin.contains("3"))
        return spanBlue + hanzi + "</span>";
    else if(pinyin.contains("4"))
        return spanPurple + hanzi + "</span>";
    else // neutral tone
        return hanzi;
}

}

#endif  COLORS_H
