#include "I_SongEntity.h"

#include <QImage>
#include <QMediaContent>
#include <QObject>

class SongEntity : public I_SongEntity
{
    Q_OBJECT
public:
    explicit SongEntity();
    ~SongEntity() override;

public:
    QImage image() override;
    QString artist() override;
    QString songName() override;
    qint64 duration() override;
    qint64 position() override;

    void setImage(QImage image) override;
    void setArtist(QString artist) override;
    void setSongName(QString songName) override;
    void setDuration(qint64 duration) override;
    void setPosition(qint64 position) override;

private:
    QImage image_;
    QString artist_;
    QString songName_;
    qint64 duration_;
    qint64 position_;
};
