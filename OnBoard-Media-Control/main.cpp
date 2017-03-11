#include "../SongPlayer/SongPlayer.h"
#include "OnBoardMediaControl.h"

int main(int argc, char *argv[])
{

    QScopedPointer<OnBoardMediaControl> app;
    app.reset(new OnBoardMediaControl(argc, argv));

    SongPlayer player;
    const QStringList arguments = QCoreApplication::arguments();
    if (arguments.size() > 1)
        player.playFile(arguments.at(1));

    player.resize(683, 384);
    player.show();

    return app->exec();
}
