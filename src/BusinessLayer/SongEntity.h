#include "I_SongEntity.h"

#include <QImage>
#include <QMediaContent>


class SongEntity : public I_SongEntity
{
public:
    SongEntity(const QMediaContent& content);

    // I_SongEntity interface
public:
    QImage image();
    QString artist();
    QString songName();
    qint64 duration();
    qint64 position();
    QMediaContent songContent();

    void setImage(QImage &image);
    void setArtist(QString &artist);
    void setSongName(QString &songName);
    void setDuration(qint64 duration);
    void setPosition(qint64 position);
    void setSongContent(QMediaContent &content);

private:
    QImage image_;
    QString artist_;
    QString songName_;
    qint64 duration_;
    qint64 position_;
    QMediaContent mediaContent_;

};
