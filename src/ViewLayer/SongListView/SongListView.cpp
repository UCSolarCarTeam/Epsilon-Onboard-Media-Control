#include <QDir>
#include "SongListView.h"
#include <QVector>

SongListView::SongListView(I_SongListUI& ui, ContainerUI& containerUI)
    :ui_(ui),
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
    QVector<QString> tempFiles =
}

