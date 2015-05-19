#ifndef HTMLDELEGATE_H
#define HTMLDELEGATE_H

#include <QAbstractTextDocumentLayout>
#include <QStyledItemDelegate>
#include <QApplication>
#include <QPainter>

// based on http://stackoverflow.com/questions/1956542/how-to-make-item-view-render-rich-html-text-in-qt

class HtmlDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    HtmlDelegate(QObject * parent) : QStyledItemDelegate(parent)
    {

    }

protected:
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};




#endif // HTMLDELEGATE_H
