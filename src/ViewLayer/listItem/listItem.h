#pragma once
#include <QPushButton>
#include <QObject>
#include <QWidget>

class listItem: public QWidget
{
    Q_OBJECT
public:
    listItem(QString artist, QString name, QString path);
    ~listItem();
    void setPath(QString path);
    void setName(QString name);
    void setArtist(QString artist);
    void setButtonText();
    QString getName();
    QString getPath();
    QString getArtist();
    QPushButton* getButton();
signals:
    void songChanged(QString path);
private:
    QString artist_;
    QString name_;
    QString filepath_;
    QPushButton *listButton_;
public slots:
    void handleButtonPressed();
};

