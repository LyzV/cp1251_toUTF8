#include <QCoreApplication>
#include "q2utf8.h"
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QTextStream>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString indir, outdir;
    QStringList filters;


    if(2>argc)
    {
        indir=QDir::currentPath();
        outdir=indir;
        filters.append("*.h");
        filters.append("*.hpp");
        filters.append("*.c");
        filters.append("*.cpp");
    }
    else
    {
        for(int i=1; i<argc; ++i)
        {
            QString arg=argv[i];
            if(0==arg.compare(QString("-i")))
            {
                if(++i>=argc)
                {
                    QTextStream stream;
                    stream << "Error: failue argument quantity - " << argc;
                    qDebug() << stream.readAll();
                    a.exit(1);
                }
                else
                {
                    indir=argv[i];
                }
            }
            else if(0==arg.compare(QString("-o")))
            {
                if(++i>=argc)
                {
                    QTextStream stream;
                    stream << "Error: failue argument quantity - " << argc;
                    qDebug() << stream.readAll();
                    a.exit(1);
                }
                else
                {
                    outdir=argv[i];
                }
            }
            else if(0==arg.compare(QString("-f")))
            {
                if(++i>=argc)
                {
                    QTextStream stream;
                    stream << "Error: failue argument quantity - " << argc;
                    qDebug() << stream.readAll();
                    a.exit(1);
                }
                else
                {
                    QString filt=argv[i];
                    filters=filt.split(";");
                }
            }
            else
            {
                QTextStream stream;
                stream << "Error: failue arguments";
                qDebug() << stream.readAll();
                a.exit(1);
            }
        }
    }

    if(indir.isEmpty())
    {
        indir=QDir::currentPath();
    }
    if(outdir.isEmpty())
    {
        outdir=QDir::currentPath();
    }
    if(0==filters.count())
    {
        filters.clear();
        filters.append("*.h");
        filters.append("*.hpp");
        filters.append("*.c");
        filters.append("*.cpp");
    }


    Q2utf8 _2utf8;
    if(false==_2utf8.Convert(indir, outdir, filters))
        a.exit(2);

    a.exit(0);
}
