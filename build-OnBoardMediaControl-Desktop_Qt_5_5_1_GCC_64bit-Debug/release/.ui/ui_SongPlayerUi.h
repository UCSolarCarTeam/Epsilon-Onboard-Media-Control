/********************************************************************************
** Form generated from reading UI file 'SongPlayerUi.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SONGPLAYERUI_H
#define UI_SONGPLAYERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SongPlayerUi
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_4;
    QLabel *infoLabel;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QPushButton *nextSong;
    QPushButton *prevSong;
    QWidget *widget;
    QPushButton *playButton;
    QWidget *verticalWidget;
    QVBoxLayout *progressBarContainer;
    QLabel *labelPic;
    QLabel *mask;
    QPushButton *loopButton;
    QPushButton *shuffleButton;
    QSlider *volumeControl;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *SongPlayerUi)
    {
        if (SongPlayerUi->objectName().isEmpty())
            SongPlayerUi->setObjectName(QStringLiteral("SongPlayerUi"));
        SongPlayerUi->resize(683, 384);
        SongPlayerUi->setAutoFillBackground(false);
        SongPlayerUi->setStyleSheet(QStringLiteral("background-color:black;"));
        gridLayout = new QGridLayout(SongPlayerUi);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_4, 7, 6, 1, 1);

        infoLabel = new QLabel(SongPlayerUi);
        infoLabel->setObjectName(QStringLiteral("infoLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(infoLabel->sizePolicy().hasHeightForWidth());
        infoLabel->setSizePolicy(sizePolicy);
        infoLabel->setMinimumSize(QSize(0, 26));
        QFont font;
        font.setFamily(QStringLiteral("Nimbus Sans L"));
        font.setPointSize(16);
        infoLabel->setFont(font);
        infoLabel->setStyleSheet(QStringLiteral("color: white"));

        gridLayout->addWidget(infoLabel, 2, 6, 1, 1, Qt::AlignHCenter);

        verticalSpacer_3 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 0, 6, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 6, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 5, 2, 1, 1);

        widget_2 = new QWidget(SongPlayerUi);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy1);
        widget_2->setMinimumSize(QSize(420, 191));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        nextSong = new QPushButton(widget_2);
        nextSong->setObjectName(QStringLiteral("nextSong"));
        sizePolicy1.setHeightForWidth(nextSong->sizePolicy().hasHeightForWidth());
        nextSong->setSizePolicy(sizePolicy1);
        nextSong->setMinimumSize(QSize(101, 101));
        nextSong->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"        border-image: url(:/Resources/IconsOff/next.png);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"        border-image: url(:/Resources/IconsOn/next.png);\n"
"}"));

        gridLayout_2->addWidget(nextSong, 1, 2, 1, 1);

        prevSong = new QPushButton(widget_2);
        prevSong->setObjectName(QStringLiteral("prevSong"));
        sizePolicy1.setHeightForWidth(prevSong->sizePolicy().hasHeightForWidth());
        prevSong->setSizePolicy(sizePolicy1);
        prevSong->setMinimumSize(QSize(101, 101));
        prevSong->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"        border-image: url(:/Resources/IconsOff/previous.png);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"        border-image: url(:/Resources/IconsOn/previous.png);\n"
"}"));

        gridLayout_2->addWidget(prevSong, 1, 0, 1, 1);

        widget = new QWidget(widget_2);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(191, 191));
        playButton = new QPushButton(widget);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(30, 30, 131, 131));
        playButton->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"        border-style: solid;\n"
"        background: transparent;\n"
"        border-color: rgb(68,68,68);\n"
"        border-width: 5px;\n"
"        border-radius: 65px;\n"
"        background-image: url(:/Resources/IconsOff/play.png);\n"
"        background-position: center;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"        border-style: solid;\n"
"        background: transparent;\n"
"        border-color: rgb(68,68,68);\n"
"        border-width: 5px;\n"
"        border-radius: 65px;\n"
"        background-image: url(:/Resources/IconsOn/play.png);\n"
"        background-position: center;\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"        border-style: solid;\n"
"        background: transparent;\n"
"        border-color: rgb(68,68,68);\n"
"        border-width: 5px;\n"
"        border-radius: 65px;\n"
"        background-image: url(:/Resources/IconsOff/pause.png);\n"
"        background-position: center;\n"
"}\n"
"\n"
"QPushButton:checked:pressed\n"
"{\n"
"        border-style: soli"
                        "d;\n"
"        background: transparent;\n"
"        border-color: rgb(68,68,68);\n"
"        border-width: 5px;\n"
"        border-radius: 65px;\n"
"        background-image: url(:/Resources/IconsOn/pause.png);\n"
"        background-position: center;\n"
"}"));
        verticalWidget = new QWidget(widget);
        verticalWidget->setObjectName(QStringLiteral("verticalWidget"));
        verticalWidget->setGeometry(QRect(-2, -9, 191, 191));
        verticalWidget->setStyleSheet(QStringLiteral("background: transparent"));
        progressBarContainer = new QVBoxLayout(verticalWidget);
        progressBarContainer->setObjectName(QStringLiteral("progressBarContainer"));
        progressBarContainer->setContentsMargins(1, -1, -1, -1);
        labelPic = new QLabel(widget);
        labelPic->setObjectName(QStringLiteral("labelPic"));
        labelPic->setGeometry(QRect(30, 30, 130, 130));
        labelPic->setStyleSheet(QLatin1String("background-image: url(:/Resources/IconsOff/mask.png);\n"
"background: transparent;"));
        mask = new QLabel(widget);
        mask->setObjectName(QStringLiteral("mask"));
        mask->setGeometry(QRect(30, 30, 131, 131));
        mask->setStyleSheet(QLatin1String("image: url(:/Resources/IconsOff/mask.png);\n"
"background: transparent; "));
        labelPic->raise();
        mask->raise();
        verticalWidget->raise();
        playButton->raise();

        gridLayout_2->addWidget(widget, 1, 1, 1, 1);

        loopButton = new QPushButton(widget_2);
        loopButton->setObjectName(QStringLiteral("loopButton"));
        sizePolicy1.setHeightForWidth(loopButton->sizePolicy().hasHeightForWidth());
        loopButton->setSizePolicy(sizePolicy1);
        loopButton->setMinimumSize(QSize(50, 50));
        loopButton->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-image: url(:/Resources/IconsOff/repeat.png);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border-image: url(:/Resources/IconsOn/repeat.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"	border-image: url(:/Resources/IconsOn/repeat.png);\n"
"}\n"
"\n"
"QPushButton:checked:pressed\n"
"{\n"
"	border-image: url(:/Resources/IconsOff/repeat.png);\n"
"}"));

        gridLayout_2->addWidget(loopButton, 2, 0, 1, 1, Qt::AlignRight);

        shuffleButton = new QPushButton(widget_2);
        shuffleButton->setObjectName(QStringLiteral("shuffleButton"));
        sizePolicy1.setHeightForWidth(shuffleButton->sizePolicy().hasHeightForWidth());
        shuffleButton->setSizePolicy(sizePolicy1);
        shuffleButton->setMinimumSize(QSize(50, 50));
        shuffleButton->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-image: url(:/Resources/IconsOff/shuffle.png);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border-image: url(:/Resources/IconsOn/shuffle.png);\n"
"}\n"
"\n"
"QPushButton:checked\n"
"{\n"
"	border-image: url(:/Resources/IconsOn/shuffle.png);\n"
"}\n"
"\n"
"QPushButton:checked:pressed\n"
"{\n"
"	border-image: url(:/Resources/IconsOff/shuffle.png);\n"
"}"));

        gridLayout_2->addWidget(shuffleButton, 2, 2, 1, 1);


        gridLayout->addWidget(widget_2, 5, 6, 1, 1, Qt::AlignHCenter);

        volumeControl = new QSlider(SongPlayerUi);
        volumeControl->setObjectName(QStringLiteral("volumeControl"));
        sizePolicy.setHeightForWidth(volumeControl->sizePolicy().hasHeightForWidth());
        volumeControl->setSizePolicy(sizePolicy);
        volumeControl->setMinimumSize(QSize(16, 0));
        volumeControl->setStyleSheet(QLatin1String("QSlider::groove:vertical {\n"
"background: #5c91a1;\n"
"width: 4px;\n"
"position: absolute; \n"
"}\n"
"\n"
"QSlider::handle:vertical {\n"
"height: 16px;\n"
"border-radius: 8px;\n"
"background: grey;\n"
"margin: 0  -6px;\n"
"}\n"
"\n"
"QSlider::add-page:vertical {\n"
"background: #5c91a1;\n"
"}\n"
"\n"
"QSlider::sub-page:vertical {\n"
"background: white;\n"
"}"));
        volumeControl->setSliderPosition(99);
        volumeControl->setOrientation(Qt::Vertical);

        gridLayout->addWidget(volumeControl, 5, 9, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 8, 1, 1);


        retranslateUi(SongPlayerUi);

        QMetaObject::connectSlotsByName(SongPlayerUi);
    } // setupUi

    void retranslateUi(QWidget *SongPlayerUi)
    {
        SongPlayerUi->setWindowTitle(QApplication::translate("SongPlayerUi", "Form", 0));
        infoLabel->setText(QString());
        nextSong->setText(QString());
        prevSong->setText(QString());
        playButton->setText(QString());
        labelPic->setText(QString());
        mask->setText(QString());
        loopButton->setText(QString());
        shuffleButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SongPlayerUi: public Ui_SongPlayerUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SONGPLAYERUI_H
