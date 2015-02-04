#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebFrame>
#include <QWebElement>
#include <QKeyEvent>
#include <QWebView>
#include <QUrl>
#include <QClipboard>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // when using search form extraction, you can also use http://www.thai-language.com/dict (advanced search)
    // whith the search type choice radio button set to "exact match"

    ui->setupUi(this);
    foreach(QObject * object,this->children())
    {
        if(object->isWidgetType())
        {
            QLayout * layout = qobject_cast<QWidget*>(object)->layout();
            if(layout)
            {
                layout->setContentsMargins(1,1,1,1);
                layout->setSpacing( 1 );
            }
        }
    }

    this->setWindowIcon(QIcon(":ic_launcher.png"));

    inputForm = new InputForm(ui, this);


    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(showMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMessage()
{
    QMessageBox::information(this,QString(),ui->lineEdit->text());
}

