#include "csvtool.h"

// write CSV
bool CSVTool::WriteCSV(const QVector<QString>& headers, const QVector<QString>& keyValuePair,
                       const char* codec)
{
    QFile file(m_fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "Failed to open file for writing";
        return false;
    }

    QTextStream outFile(&file);
    outFile.setCodec(codec);

    //write heads and key-value in the csv file with exception
    try {
        // header
        outFile << headers[0] << " : " << headers[1];
        outFile << "\n";

        // key-value
        for(const QString& item : keyValuePair)
        {
            QStringList parts = item.split(" : ");
            //qDebug() << parts.size() << "\n";
            if(parts.size() != 2)
            {
                throw std::runtime_error("Data format is invalid");
            }
            outFile << parts[0] << " : " << parts[1];
            outFile << "\n";
        }


    } catch (const std::exception& ex) {
        qDebug() << "Error while writing csv: " << ex.what();
        file.close();

        return false;
    }

    file.close();
    return true;
}

// read CSV
QVector<QString> CSVTool::ReadCSV()
{

}
