#include "ContainerUI.h"
#include "ui_ContainerUI.h"
#include <QStyle>
#include <QDesktopWidget>

ContainerUI::ContainerUI(QWidget *parent) :
    QStackedWidget(parent),
    containerUI_(new Ui::ContainerUI)
{
    containerUI_->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignBottom,
            size(),
            qApp->desktop()->availableGeometry()
        )
    );
    show();
}

ContainerUI::~ContainerUI()
{
    delete containerUI_;
}
