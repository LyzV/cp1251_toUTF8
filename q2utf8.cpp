#include "q2utf8.h"
#include <QDebug>
#include <QTextStream>
#include <QByteArray>

Q2utf8::Q2utf8()
{
    codec=QTextCodec::codecForName("CP1251");
}

void Q2utf8::array2utf8(const QByteArray &inb, QString &outs)
{
    outs=codec->toUnicode(inb);
}

bool Q2utf8::convert(QDir &indir, QDir &outdir, const QStringList &file_filters)
{
    if(false==_convert_dir(indir, outdir, file_filters))
    {
        return false;
    }

    return true;

//    if(false==outdir.exists())
//    {
//        if(false==outdir.mkdir(outdir.path()))
//        {
//            QTextStream stream;
//            stream << "Error: can not make directory \"" << outdir.path();
//            qDebug() << stream.readAll();
//            return false;
//        }
//    }

//    QFileInfoList dir_info_list=indir.entryInfoList(dir_filters, QDir::Dirs);
//    for(int i=0; i<dir_info_list.count(); ++i)
//    {
//        QString indir_name=indir.path()+'/'+dir_info_list.at(i).fileName();
//    }
    //    return true;
}

bool Q2utf8::Convert(const QString &indir_name, const QString &outdir_name, const QStringList &file_filters)
{
    QDir indir(indir_name);
    QDir outdir(outdir_name);
    return convert(indir, outdir, file_filters);

}

//void Q2utf8::_convert_file(QFile &infile, QFile &outfile)
//{
//    QByteArray bytes=infile.readAll();
//    QString outs;
//    array2utf8(bytes, outs);
//    outfile.write(outs.toUtf8());
//}

bool Q2utf8::_convert_dir(QDir &indir,
                      QDir &outdir,
                      const QStringList &file_filters)
{
    QFileInfoList file_info_list=indir.entryInfoList(file_filters, QDir::Files);
    //Сначала текущую директорию
    for(int i=0; i<file_info_list.count(); ++i)
    {
        QString infile_name=indir.path()+'/'+file_info_list.at(i).fileName();
        QFile infile(infile_name);
        if(false==infile.exists())
        {
            QTextStream stream;
            stream << "Error: file \"" << infile.fileName() << "\" does not exist!";
            qDebug() << stream.readAll();
            return false;
        }
        if(false==infile.open(QIODevice::ReadOnly))
        {
            QTextStream stream;
            stream << "Error: can not open file \"" << infile.fileName();
            qDebug() << stream.readAll();
            return false;
        }
        QByteArray bytes=infile.readAll();
        infile.close();

        QString outfile_name=outdir.path()+'/'+file_info_list.at(i).fileName();
        QFile outfile(outfile_name);
        if(true==outfile.exists())
        {
            if(false==outfile.remove())
            {
                QTextStream stream;
                stream << "Error: can not remove file \"" << outfile.fileName();
                qDebug() << stream.readAll();
                return false;
            }
        }
        if(false==outfile.open(QIODevice::WriteOnly))
        {
            QTextStream stream;
            stream << "Error: can not open file \"" << outfile.fileName();
            qDebug() << stream.readAll();
            return false;
        }
        QString outs;
        array2utf8(bytes, outs);
        outfile.write(outs.toUtf8());
        outfile.close();
    }
    //Потом все вложенные
    QFileInfoList dir_info_list=indir.entryInfoList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
    //Сначала текущую директорию
    for(int i=0; i<dir_info_list.count(); ++i)
    {
        QString in_in_dir_name=dir_info_list.at(i).filePath();
        QDir in_in_dir(in_in_dir_name);
        if(false==in_in_dir.exists())
        {
            QTextStream stream;
            stream << "Error: directory \"" << in_in_dir.path() << "\" does not exist!";
            qDebug() << stream.readAll();
            return false;
        }
        QString out_out_dir_name=outdir.path()+'/'+dir_info_list.at(i).fileName();
        QDir out_out_dir(out_out_dir_name);
        if(false==out_out_dir.exists())
        {
            if(false==out_out_dir.mkdir(out_out_dir_name))
            {
                QTextStream stream;
                stream << "Error: can not create directory \"" << out_out_dir.path();
                qDebug() << stream.readAll();
                return false;
            }
        }
        if(false==_convert_dir(in_in_dir, out_out_dir, file_filters))
        {
            return false;
        }
    }
    return true;
}
