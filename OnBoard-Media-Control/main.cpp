#include "../song_player/SongPlayer.h"

#include <QApplication>
#include <QFileInfo>
#include <QSettings>
#include <QIcon>
#include <QDir>

static void associateFileTypes(const QStringList &fileTypes)
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

    settings.beginGroup("shell");
    settings.beginGroup("open");
    settings.setValue("SongPlayer", displayName);
    settings.beginGroup("Command");
    settings.setValue(".", QChar('"') + QDir::toNativeSeparators(filePath) + QString("\" \"%1\""));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("MusicPlayer");
    app.setOrganizationDomain("qt-project.org");
    app.setApplicationDisplayName("Music Player");

    associateFileTypes(QStringList(".mp3"));

    SongPlayer player;
    const QStringList arguments = QCoreApplication::arguments();
    if (arguments.size() > 1)
        player.playFile(arguments.at(1));
    player.resize(300, 60);
    player.show();

    return app.exec();
}
