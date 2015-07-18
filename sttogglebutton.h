#ifndef STTOGGLEBUTTON_H
#define STTOGGLEBUTTON_H

#include <QWidget>
#include <QToolButton>


/**
 * @brief The STToggleButton has checked states, where non-checked means 简 and checked (pressed) means 繁
 */
class STToggleButton : public QToolButton
{
    Q_OBJECT
public:
    explicit STToggleButton(QWidget *parent = 0);
    ~STToggleButton();

signals:

private slots:
    // toggle between simplified and traditional characters
    void onToggled(bool b);
};

#endif // STTOGGLEBUTTON_H
