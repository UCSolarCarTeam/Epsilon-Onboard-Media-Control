#include <QFontDatabase>
#include "FontLoader.h"

FontLoader::FontLoader()
{
    fontHash_[Font::BURLINGAME] = QFontDatabase::addApplicationFont(":/Resources/Fonts/BurlingamePro-Light.otf");
}

QFont FontLoader::loadFont(Font value)
{
    QString family = QFontDatabase::applicationFontFamilies(fontHash_[value]).at(0);
    return QFont(family);
}

QFont FontLoader::loadFont(Font value, int pointSize, bool bold)
{
    QString family = QFontDatabase::applicationFontFamilies(fontHash_[value]).at(0);
    QFont font(family);
    font.setPointSize(pointSize);
    font.setBold(bold);
    return font;
}
