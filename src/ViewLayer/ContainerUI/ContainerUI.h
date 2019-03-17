#pragma once

#include <QStackedWidget>

namespace Ui {
class ContainerUI;
}

class ContainerUI : public QStackedWidget
{
    Q_OBJECT

public:
    explicit ContainerUI(QWidget *parent = nullptr);
    ~ContainerUI();

private:
    Ui::ContainerUI *containerUI_;
};


