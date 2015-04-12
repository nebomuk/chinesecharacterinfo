#include "convertpinyin.h"
#include <QMap>
#include <qstringlist.h>


ConvertPinyin::ConvertPinyin()
{

}

/*static*/ QString ConvertPinyin::ConvertNumericalPinYinToAccented(QString input)
    {
    // TODO port regex
//        QMap<int, QString> pinyinToneMark;
//        pinyinToneMark.insert(0, "aoeiuv\u00fc");
//        pinyinToneMark.insert(1, "\u0101\u014d\u0113\u012b\u016b\u01d6\u01d6");
//        pinyinToneMark.insert(2, "\u00e1\u00f3\u00e9\u00ed\u00fa\u01d8\u01d8");
//        pinyinToneMark.insert(3, "\u01ce\u01d2\u011b\u01d0\u01d4\u01da\u01da");
//        pinyinToneMark.insert(4, "\u00e0\u00f2\u00e8\u00ec\u00f9\u01dc\u01dc");

//        QStringList words = input.split(' ');
        QString accented = "";
//        QString t = "";
//        foreach (QString pinyin, words)
//        {
//            for(QString::ConstIterator it = pinyin.begin(); it< pinyin.end(); ++it)
//            {
//                QChar c = *it;
//                if (c >= 'a' && c <= 'z')
//                {
//                    t += c;
//                }
//                else if (c == ':')
//                {
//                    if (t[t.length() - 1] == 'u')
//                    {
//                        t = t.left(t.length() - 2) + "\u00fc";
//                    }
//                }
//                else
//                {
//                    if (c >= '0' && c <= '5')
//                    {
//                        int tone = c.toAscii() % 5;

//                        if (tone != 0)
//                        {
//                            Match match = Regex.Match(t, "[aoeiuv\u00fc]+");
//                            if (!match.Success)
//                            {
//                                t += c;
//                            }
//                            else if (match.Groups[0].length() == 1)
//                            {
//                                t = t.left(match.Groups[0].Index) +
//                                    pinyinToneMark[tone][pinyinToneMark[0].indexOf(match.Groups[0].Value[0])] // TODO use QRegexp::capturedTexts
//                                    + t.left(match.Groups[0].Index + match.Groups[0].length());
//                            }
//                            else
//                            {
//                                if (t.contains("a"))
//                                {
//                                    t = t.replace("a", QChar(pinyinToneMark[tone][0]));
//                                }
//                                else if (t.contains("o"))
//                                {
//                                    t = t.replace("o", QChar(pinyinToneMark[tone][1]));
//                                }
//                                else if (t.contains("e"))
//                                {
//                                    t = t.replace("e", QChar(pinyinToneMark[tone][2]));
//                                }
//                                else if (t.contains("ui"))
//                                {
//                                    t = t.replace("i", QChar(pinyinToneMark[tone][3]));
//                                }
//                                else if (t.contains("iu"))
//                                {
//                                    t = t.replace("u", QChar(pinyinToneMark[tone][4]));
//                                }
//                                else
//                                {
//                                    t += "!";
//                                }
//                            }
//                        }
//                    }
//                    accented += t;
//                    t = "";
//                }
//            }
//            accented += t + " ";
//        }
//        accented = accented.trimmed();
        return accented;
    }
