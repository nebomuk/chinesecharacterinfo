#include "sttogglebutton.h"

STToggleButton::STToggleButton(QWidget *parent) : QToolButton(parent)
{
    setCheckable(true);
    state_ = Simplified;
    connect(this,SIGNAL(toggled(bool)),this,SLOT(onToggled(bool)));
    setText(QString::fromUtf8("简"));
}

STToggleButton::~STToggleButton()
{

}

void STToggleButton::onToggled(bool b)
{
    setText(b? QString::fromUtf8("繁") : QString::fromUtf8("简"));
    state_ = b? Traditional : Simplified;
}

STToggleButton::State STToggleButton::state() const
{
    return state_;
}


