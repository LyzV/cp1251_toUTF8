#ifndef Q2UTF8_H
#define Q2UTF8_H

#include <QByteArray>
#include <QStringList>
#include <QTextCodec>
#include <QDir>
#include <QFile>

class Q2utf8
{
    QTextCodec *codec;

    //void _convert_file(QFile &infile, QFile &outfile);
    bool _convert_dir(QDir &indir, QDir &outdir, const QStringList &file_filters);

public:
    Q2utf8();
    void array2utf8(const QByteArray &inb, QString &outs);
    bool convert(QDir &indir, QDir &outdir, const QStringList &file_filters);
    bool Convert(const QString &indir_name, const QString &outdir_name,
                 const QStringList &file_filters);

};

#endif // Q2UTF8_H
