/********************************************************************************
** Form generated from reading UI file 'songplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SONGPLAYER_H
#define UI_SONGPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicPlayer
{
public:
    QMenuBar* menuBar;
    QToolBar* mainToolBar;
    QWidget* centralWidget;
    QStatusBar* statusBar;

    void setupUi(QMainWindow* MusicPlayer)
    {
        if (MusicPlayer->objectName().isEmpty())
        {
            MusicPlayer->setObjectName(QStringLiteral("MusicPlayer"));
        }

        MusicPlayer->resize(400, 300);
        menuBar = new QMenuBar(MusicPlayer);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MusicPlayer->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MusicPlayer);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MusicPlayer->addToolBar(mainToolBar);
        centralWidget = new QWidget(MusicPlayer);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MusicPlayer->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MusicPlayer);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MusicPlayer->setStatusBar(statusBar);

        retranslateUi(MusicPlayer);

        QMetaObject::connectSlotsByName(MusicPlayer);
    } // setupUi

    void retranslateUi(QMainWindow* MusicPlayer)
    {
        MusicPlayer->setWindowTitle(QApplication::translate("MusicPlayer", "MusicPlayer", 0));
    } // retranslateUi

};

namespace Ui
{
    class MusicPlayer: public Ui_MusicPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SONGPLAYER_H
