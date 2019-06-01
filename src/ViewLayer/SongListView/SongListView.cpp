#include <QDir>
#include "SongListView.h"
#include <QVector>
#include <QDebug>

SongListView::SongListView(SongPlayer& songPlayer, I_SongListUI& ui, ContainerUI& containerUI)
    :songPlayer_(songPlayer),
     ui_(ui),
     containerUI_(containerUI)
{
    addSongsToList();
    connect(&ui_.listToPlayer(), SIGNAL(clicked()), this, SLOT(handleListToPlayerClicked()));
}

SongListView::~SongListView()
{
}

void SongListView::handleListToPlayerClicked()
{
    containerUI_.setCurrentIndex(0);
}

void SongListView::addSongsToList()
{
    addFilePaths();
}

void SongListView::addFilePaths()
{
    QVector<QString> tempFiles = songPlayer_.getController()->getFiles();
    for(int i = 0; i<tempFiles.length(); i++){
        listItem temp;
        temp.setPath(tempFiles.at(i));
        int w = songPlayer_.loadMetaData(temp.getPath());
        if(w==-1)
        {
            qDebug() << "Error loading meta data for song at index " << i;
        }
        temp.setName(songPlayer_.getSongName());
        temp.setArtist(songPlayer_.getSongArtist());
        infoList_.push_back(&temp);
        qDebug() << temp.getName() << " " << temp.getArtist() << " " << temp.getPath();
     }

}

