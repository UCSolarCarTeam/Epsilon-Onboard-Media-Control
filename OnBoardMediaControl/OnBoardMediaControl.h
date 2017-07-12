#include <QApplication>
#include <QFileInfo>
#include <QSettings>
#include <QIcon>
#include <QDir>

class OnBoardMediaControl : public QApplication
{
public:
    OnBoardMediaControl(int& argc, char** argv);

    void associateFileTypes(const QStringList& fileTypes);
};
