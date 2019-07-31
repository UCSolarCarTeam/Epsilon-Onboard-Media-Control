#include <QDir>
#include "SongListView.h"
#include <QVector>
#include <QDebug>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QPixmap>
#include "listItem/listItem.h"

QString SCROLLBAR_STYLESHEET = "QScrollBar:vertical {"
                                   "    background:rgba(83, 83, 84);"
                                   "    width:10px;    "
                                   "    margin: 0px 0px 0px 0px;"
                                   "}"
                                   "QScrollBar::handle:vertical {"
                                   "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                   "    stop: 0 rgb(255, 192, 33), stop: 0.5 rgb(255, 192, 33), stop:1 rgb(255, 192, 33));"
                                   "    min-height: 0px;"
                                   "    border-radius: 5px;"
                                   "}"
                                   "QScrollBar::add-line:vertical {"
                                   "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                   "    stop: 0 rgb(255, 192, 33), stop: 0.5 rgb(255, 192, 33),  stop:1 rgb(255, 192, 33));"
                                   "    height: 0px;"
                                   "    subcontrol-position: bottom;"
                                   "    subcontrol-origin: margin;"
                                   "}"
                                   "QScrollBar::sub-line:vertical {"
                                   "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                   "    stop: 0  rgb(255, 192, 33), stop: 0.5 rgb(255, 192, 33),  stop:1 rgb(255, 192, 33));"
                                   "    height: 0 px;"
                                   "    subcontrol-position: top;"
                                   "    subcontrol-origin: margin;"
                                   "}";

SongListView::SongListView(SongPlayer& songPlayer, I_SongListUI& ui, ContainerUI& containerUI, I_SongPlayerUi& songPlayerUI)
    :songPlayer_(songPlayer),
     ui_(ui),
     containerUI_(containerUI),
     songPlayerUI_(songPlayerUI),
     infoList_()
{
    QScrollBar* verticalBar = new QScrollBar();
    verticalBar->setStyleSheet(SCROLLBAR_STYLESHEET);
    ui_.listScroll().setVerticalScrollBar(verticalBar);
    ui_.listScroll().setStyleSheet("border-style: outset; border-width: 1px; border-color:grey;");
    addSongsToList();
    connect(&ui_.listToPlayer(), SIGNAL(clicked()), this, SLOT(handleListToPlayerClicked()));
}

SongListView::~SongListView()
{
    for(int j = 0; j<infoList_.length(); j++)
    {
        delete infoList_[j];
    }
}

void SongListView::handleListToPlayerClicked()
{
    containerUI_.setCurrentIndex(0);
}

void SongListView::handleSongButtonClicked(QString path)
{
    songPlayer_.setFile(path);
    songPlayerUI_.playButton().setChecked(true);
    handleListToPlayerClicked();
}


void SongListView::addSongsToList()
{
    addFilePaths();
    QLayout* layoutL = ui_.scrollAreaWidgetContents().layout();
    int j = 0;
    for(; j<infoList_.length(); j++){
        layoutL->addWidget(infoList_[j]->getButton());
        connect(infoList_[j], SIGNAL(songChanged(QString)), this, SLOT(handleSongButtonClicked(QString)));
    }
    ui_.scrollAreaWidgetContents().setFixedSize(ui_.width() - 50, j * 35);
}

void SongListView::addFilePaths()
{
    QVector<QString> tempFiles = songPlayer_.getController()->getFiles();
    for(int i = 0; i<tempFiles.length(); i++)
    {
        int errorCheck = songPlayer_.loadMetaData(tempFiles.at(i));
        if(errorCheck==-1)
        {
            qDebug() << "Error loading meta data for song at index " << i;
            exit(-1);
        }
        listItem *temp = new listItem(songPlayer_.getSongArtist(), songPlayer_.getSongName(), tempFiles.at(i));
        infoList_.push_back(temp);
     }
}

