#pragma once

#include <QObject>
#include <QHash>
#include <QFont>

enum Font { BURLINGAME, LCD };
class FontLoader
{
public:
    FontLoader();
    QFont loadFont(Font value);
    QFont loadFont(Font value, int pointSize, bool bold);

private:
    QHash<Font, int> fontHash_;
};
