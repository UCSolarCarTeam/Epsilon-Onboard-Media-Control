#include <QDir>
#include "SongListView.h"
#include <QVector>
#include <QDebug>
#include <QScrollBar>
#include <QVBoxLayout>

SongListView::SongListView(SongPlayer& songPlayer, I_SongListUI& ui, ContainerUI& containerUI)
    :songPlayer_(songPlayer),
     ui_(ui),
     containerUI_(containerUI),
     infoList_()
{

//    ui_.listScroll().setWidget(new QVBoxLayout());
    QScrollBar* verticalBar = new QScrollBar();
    ui_.listScroll().setVerticalScrollBar(verticalBar);
    addSongsToList();
    connect(&ui_.listToPlayer(), SIGNAL(clicked()), this, SLOT(handleListToPlayerClicked()));
}

SongListView::~SongListView()
{
    for(int j = 0; j<infoList_.length(); j++){
        delete infoList_[j];
    }
}

void SongListView::handleListToPlayerClicked()
{
    containerUI_.setCurrentIndex(0);
}

void SongListView::addSongsToList()
{
    addFilePaths();
    QLayout* layoutL = ui_.scrollAreaWidgetContents().layout();
    for(int j = 0; j<infoList_.length(); j++){
        layoutL->addWidget(infoList_[j]);
    }
}

void SongListView::addFilePaths()
{
    QVector<QString> tempFiles = songPlayer_.getController()->getFiles();
    for(int i = 0; i<tempFiles.length(); i++){
        int w = songPlayer_.loadMetaData(tempFiles.at(i));
        if(w==-1)
        {
            qDebug() << "Error loading meta data for song at index " << i;
            exit(-1);
        }
        infoList_.push_back(new listItem(songPlayer_.getSongArtist(), songPlayer_.getSongName(), tempFiles.at(i)));
//        qDebug() << temp.getName() << " " << temp.getArtist() << " " << temp.getPath();
     }
}

