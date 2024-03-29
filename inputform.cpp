#include "dictloader_edict.h"
#include "dictloadersep.h"
#include "inputform.h"

#include <QWebElement>
#include <QApplication>
#include <QClipboard>
#include <QWebFrame>
#include <QKeyEvent>
#include <QMetaMethod>
#include <QHash>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QtNetwork/QNetworkRequest>
#include <QDebug>
#include <QNetworkReply>
#include "htmldelegate.h"

InputForm::InputForm(Ui::MainWindow * ui, QObject *parent) :
    QObject(parent)
{
    ui_ = ui;
    RTHLineEdit_ = ui->lineEdit;
     translationLineEdit_ = ui->translationLineEdit;
     translationEnLineEdit_ = ui->translationEnLineEdit;
     webView_ = ui->webView;
//     webView1_ = ui->webView1; // currently not in layout
     ceTextEdit_ = ui->ceTextEdit;


     hanziSearch = new HanziSearch;
     QString dictFile = qApp->applicationDirPath() + "/" + "hande_cedict.txt"; // can be found in /home/user/Chinese/Tables/
     if(!QFile::exists(dictFile))
     {
         if(QSettings().contains("dictFile")) // try to read from settings
         {
             dictFile = QSettings().value("dictFile").toString();
         }
         if(!QFile::exists(dictFile)) // check if settings still correct
         {
             QMessageBox::warning(0,"Dictionary Does not exist", "Dictionary file hande_cedict.txt not found in the application directory path or in the last location");
             dictFile = QFileDialog::getOpenFileName(0,"Select Dictionary File");
         }
         if(dictFile.isEmpty()) // no file chosen - exit
             qApp->quit();
     }
     QSettings().setValue("dictFile", dictFile);
     dictLoader = new DictLoaderSep(dictFile);
     dictLoaderEn = QSharedPointer<DictLoaderEdict>(new DictLoaderEdict());

     // initializes ictLoaderEn   adjLoader    decLoader
     loadSimplified();

     adjModel_ = new QStringListModel(this);
     decModel_ = new QStringListModel(this);

     ui_->adjListView->setModel(adjModel_);
     ui_->adjListView->setItemDelegate(new HtmlDelegate(this));


     ui_->decListView->setModel(decModel_);
     ui_->decListView->setItemDelegate(new HtmlDelegate(this));



    // info: /print would argument will hide the left border
   // ui->webView->load(QUrl("http://www.thai-language.com"));

     //QUrl("http://localhost/taegl-chin-offline/"));
    webView_->load(QUrl("http://taeglich.chinesisch-trainer.de/index.php"));
//    webView1_->load(QUrl("http://www.chineseetymology.org/CharacterEtymology.aspx?characterInput=%E8%BB%8A&submitButton1=Etymology"));
    //webView1_->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, false);

    connect(webView_,SIGNAL(loadFinished(bool)),this,SLOT(onLoadFinished(bool)));
//    connect(webView1_,SIGNAL(loadFinished(bool)),this,SLOT(onLoadFinished1(bool)));

    clipboard = QApplication::clipboard();
    connect(clipboard,SIGNAL(changed(QClipboard::Mode)),this,SLOT(clipboardChanged(QClipboard::Mode)));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    connect(ui_->adjListView,SIGNAL(clicked(QModelIndex)),this,SLOT(onAdjListItemClicked(QModelIndex)));
    connect(ui_->decListView,SIGNAL(clicked(QModelIndex)),this,SLOT(onDecListItemClicked(QModelIndex)));
    connect(ui_->stToggleButton,SIGNAL(toggled(bool)),this,SLOT(stToggle(bool)));

}

void InputForm::onLoadFinished(bool)
{
        QWebFrame *frame = webView_->page()->mainFrame();

        QWebElement element = frame->findFirstElement("#logo");
        element.setAttribute("style", "display: none");
        frame->scroll(16,186);
}

void InputForm::onAdjListItemClicked(QModelIndex index)
{
    int rowIndex = index.row();
    QString str = adjModel_->stringList().at(rowIndex);
    if(str > 0)
    {
        currentChar = str.remove(QRegExp("<[^>]*>")).at(0);
        updateModels(); // remove html and take first char (chinese char)
    }
}

void InputForm::onDecListItemClicked(QModelIndex index)
{
    int rowIndex = index.row();
    QString str = decModel_->stringList().at(rowIndex);
    if(str > 0)
    {
        currentChar = str.remove(QRegExp("<[^>]*>")).at(0);
        updateModels();
    }
}

void InputForm::loadSimplified()
 {
    adjLoader = QSharedPointer<AdjDecLoader>(new AdjDecLoader(":AdjList.txt",dictLoaderEn->getDict(),AdjDecLoader::Simplified));
    decLoader = QSharedPointer<AdjDecLoader>(new AdjDecLoader(":decomp.txt",dictLoaderEn->getDict(), AdjDecLoader::Simplified));
    this->updateModels();
}

void InputForm::loadTraditional()
{
    adjLoader = QSharedPointer<AdjDecLoader>(new AdjDecLoader(":AdjListT.txt",dictLoaderEn->getDictT(),AdjDecLoader::Traditional));
    decLoader = QSharedPointer<AdjDecLoader>(new AdjDecLoader(":decompT.txt",dictLoaderEn->getDictT(),AdjDecLoader::Traditional));
    this->updateModels();
}

void InputForm::stToggle(bool pressed)
{

    if(pressed)
    {
        currentChar = dictLoaderEn->s2T(currentChar);
        loadTraditional();
    }
    else
    {
        currentChar = dictLoaderEn->t2S(currentChar);
        loadSimplified();
    }

}


void InputForm::updateModels()
{
    if(currentChar.isNull())
        return;

    QString translation =  currentChar + " " + dictLoader->getDict().value(currentChar);

    QString def = dictLoaderEn->getDict().value(currentChar); // simp def
    if(def.isEmpty())
        def = dictLoaderEn->getDictT().value(currentChar); // trad def

    QString translationEn = currentChar + " " + def;
    translationLineEdit_->setText(translation);
    translationLineEdit_->home(false);
    translationEnLineEdit_->setText(translationEn);
    translationEnLineEdit_->home(false);
    RTHLineEdit_->setText(hanziSearch->getText(currentChar));
    RTHLineEdit_->home(false);

    decModel_->setStringList(decLoader->getText(currentChar));
    adjModel_->setStringList(adjLoader->getText(currentChar,true));


//    webView1_->load(QUrl("http://www.chineseetymology.org/CharacterEtymology.aspx?characterInput=" + currentChar +"&submitButton1=Etymology"));



    QWebFrame *frame = webView_->page()->mainFrame();

        //QWebElement searchElement = frame->findFirstElement("#search");
        QWebElement searchElement = frame->findFirstElement("[name=c]");

        searchElement.setAttribute("value",currentChar);
        searchElement.setFocus();
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
        webView_->event(&keyEvent);

        manager->get(QNetworkRequest(QUrl("http://www.chineseetymology.org/CharacterEtymology.aspx?characterInput=" + currentChar +"&submitButton1=Etymology")));
}

void InputForm::clipboardChanged(QClipboard::Mode mode)
{
//    QWidget * parent = qobject_cast<QWidget*>(this->parent());
//    if(parent)
//    {
//        // dont waste cpu and bandwidth if the window is not visible
//        if(parent->isHidden() || parent->isMinimized() || !parent->isVisible())
//            return;
//    }

    QString text;
    if(mode == QClipboard::Selection)
    text = clipboard->text(QClipboard::Selection).trimmed();
    else
    text = clipboard->text(QClipboard::Clipboard).trimmed();

    if(text.isEmpty())
        return;

    QRegExp isHan("([\\x3400-\\x9FFF\\xF900-\\xFAFF]|[\\xD840-\\xD87F][\\xDC00-\\xDFFF])+");
    if(isHan.indexIn(text) == -1)
        return;

    QChar firstChar = isHan.cap().at(0); // captured regex
    if(ui_->stToggleButton->state() == STToggleButton::Simplified)
    {
        currentChar = dictLoaderEn->t2S(firstChar);
    }
    else // state == Traditional
    {
        currentChar = dictLoaderEn->s2T(firstChar);
    }


    updateModels();
}


void InputForm::replyFinished(QNetworkReply *reply)
{
    QByteArray bytes=reply->readAll();
    QString data = QString::fromUtf8(bytes.data(), bytes.size());
    QString etymologyLabel = "<span id=\"etymologyLabel\"><p>";
    int startIdx = data.indexOf(etymologyLabel) + etymologyLabel.length(); // This is blank / empty
    int endIdx = data.indexOf("<br", startIdx);
    QString etymology = endIdx == -1 ? "No Entry" : data.mid(startIdx, endIdx - startIdx); //dooes not work
    ceTextEdit_->setText(etymology);
    reply->deleteLater();
}


// chineseetymology.org
//void InputForm::onLoadFinished1(bool)
//{
//        QWebFrame *frame = webView1_->page()->mainFrame();

//        QWebElement element = frame->findFirstElement("p");
//        element.setAttribute("style", "display: none");
//        QWebElement element1 = frame->findFirstElement("tr");
//        element1.setAttribute("style", "display: none");
//        frame->scroll(148,0);
//}

/**
 * deprecated code to search for a hanzi on taeglich-chinesisch.de
 *  you can directly put the hanzi in the url
 */

// DEPRECATED
//void InputForm::onLoadFinished(bool)
//{
//    QWebFrame *frame = webView_->page()->mainFrame();

//    //QWebElement searchElement = frame->findFirstElement("#search"); // id search
//    QWebElement searchElement = frame->findFirstElement("[name=c]"); // (name) attribute search

//    searchElement.setAttribute("value","test");
//searchElement.setFocus();
//    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
//    webView_->event(&keyEvent);


//    //QWebFrame *frame = webView_->page()->mainFrame();
//    //QWebElement  docElement = frame->documentElement();
//    //docElement.findFirst("input[id=tl-left-column]").removeFromDocument(); // does not work

//    // this would work
////    webView_->page()->mainFrame()->evaluateJavaScript("document.getElementById('tl-left-column').style.display=\"none\";"
//    //                                                         "document.getElementsByTagName('table')[0].style.display=\"none\";");
//}
