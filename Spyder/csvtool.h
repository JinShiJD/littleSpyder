#ifndef CSVTOOL_H
#define CSVTOOL_H

#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <stdexcept>


class CSVTool
{
public:
    explicit CSVTool(const QString& fileName):m_fileName(fileName){};

    // write CSV
    bool WriteCSV(const QVector<QString>& headers, const QVector<QString>& keyValuePair,
                  const char* codec);

    // read CSV
    //QVector<QVector<QString>> ReadCSV();
    QVector<QString> ReadCSV();

private:
   QString m_fileName;
};

#endif // CSVTOOL_H
