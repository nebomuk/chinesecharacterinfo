#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inputform.h"


#include <QMainWindow>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showMessage();
    
private:
    Ui::MainWindow *ui;

    InputForm  * inputForm;
};

#endif // MAINWINDOW_H
