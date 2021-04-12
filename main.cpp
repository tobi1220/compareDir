#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDirIterator>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDirIterator *it = new QDirIterator(QCoreApplication::arguments().at(1), QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QFile *file = nullptr;
    QSet<QByteArray> set;
    while (it->hasNext()) {
        file = new QFile(it->next());
        file->open(QIODevice::ReadOnly);
        set.insert(QCryptographicHash::hash(file->readAll(), QCryptographicHash::Md5));
        file->close();
        delete file;
    }
    delete it;
    it = new QDirIterator(QCoreApplication::arguments().at(2), QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it->hasNext()) {
        file = new QFile(it->next());
        file->open(QIODevice::ReadOnly);
        if (set.contains(QCryptographicHash::hash(file->readAll(), QCryptographicHash::Md5))) {
            file->remove();
        } else {
            file->close();
        }
        delete file;
    }
    delete it;

    return 0;
}
