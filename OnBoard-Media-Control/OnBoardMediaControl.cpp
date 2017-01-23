#include "OnBoardMediaControl.h"
#include "../song_player/SongPlayer.h"

OnBoardMediaControl::OnBoardMediaControl(int &argc, char **argv)
    : QApplication(argc, argv)
{
    setApplicationName("MusicPlayer");
    setApplicationDisplayName("Music Player");

    associateFileTypes(QStringList(".mp3"));
}

void OnBoardMediaControl::associateFileTypes(const QStringList &fileTypes)
{
    QString displayName = QGuiApplication::applicationDisplayName();
    QString filePath = QCoreApplication::applicationFilePath();
    QString fileName = QFileInfo(filePath).fileName();

    QSettings settings(fileName, QSettings::NativeFormat);
    settings.setValue("SongPlayer", displayName);

    settings.beginGroup("SupportedTypes");
    foreach (const QString& fileType, fileTypes)
        settings.setValue(fileType, QString());
    settings.endGroup();

    settings.beginGroup("open");
    settings.setValue("SongPlayer", displayName);
    settings.beginGroup("Command");
    settings.setValue(".", QChar('"') + QDir::toNativeSeparators(filePath) + QString("\" \"%1\""));
}
