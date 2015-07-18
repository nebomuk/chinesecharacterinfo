#ifndef INPUTFORM_H
#define INPUTFORM_H

#include "adjdecloader.h"
#include "dictloader_edict.h"
#include "dictloadersep.h"
#include "hanzisearch.h"

#include <QObject>
#include <QWebView>
#include <QClipboard>
#include <QLineEdit>
#include <ui_mainwindow.h>
#include <QStringListModel>
// copys the text from the clipboard and calls a certain input form in the webview

class InputForm : public QObject
{
    Q_OBJECT
public:
    explicit InputForm(Ui::MainWindow *ui, QObject *parent = 0);
    
    void updateModels(QString text);
    void loadSimplified();
    void loadTraditional();
public slots:
    
private slots:
    void onLoadFinished(bool);
    void clipboardChanged(QClipboard::Mode mode);

    void replyFinished(QNetworkReply *reply);
    void onAdjListItemClicked(QModelIndex index);
    void onDecListItemClicked(QModelIndex index);
    void stToggle(bool pressed); // toggle between simplified and traditional characters
private:
     QWebView *webView_;
//     QWebView *webView1_;
     QLineEdit * RTHLineEdit_;
     QLineEdit * translationLineEdit_;
     QLineEdit *translationEnLineEdit_;
     QTextEdit * decTextEdit_;
     QTextEdit *adjTextEdit_;
     HanziSearch * hanziSearch;
     QSharedPointer<AdjDecLoader> adjLoader;
     QSharedPointer<AdjDecLoader> decLoader;
     DictLoaderSep * dictLoader;
     QSharedPointer<DictLoaderEdict> dictLoaderEn;
     QClipboard * clipboard;
     QNetworkAccessManager *manager;
     QTextEdit *ceTextEdit_;
     Ui::MainWindow *ui_;
     QStringListModel * adjModel_;
     QStringListModel * decModel_;
};

#endif // INPUTFORM_H
