#include <QCoreApplication>
#include "httpaccess.h"
#include <QRegularExpression>
#include "retool.h"
#include "csvtool.h"
#include <QTimer>

void Exit()
{
    QCoreApplication::exit();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HttpAccess httpAccess;
    RETool reTool("<li class=\"hotsearch-item[\\s\\S]*?href=\"([\\s\\S]*?)\"[\\s\\S]*?<span class=\"title-content-title\">([\\s\\S]*?)</span>");

    CSVTool csvTool("spyder.csv");
    QVector<QString> headers = {"title", "url"};

    QObject::connect(&httpAccess, &HttpAccess::finished, [&](const QString& data){
        //qDebug() << data;
//        QRegularExpression regex("<li class=\"hotsearch-ite[\\s\\S]*?href=\"([\\s\\S]*?)\"[\\s\\S]*?<span class=\"title-content-title\">([\\s\\S]*?)</span>");

//        QRegularExpressionMatchIterator i = regex.globalMatch(data);
//        while(i.hasNext())
//        {
//            QRegularExpressionMatch match = i.next();
//            QString matchedInfo = match.captured(2) + ":" + match.captured(1);
//            qDebug() << "Matched: " << matchedInfo;
//        }

//        // 控制台显示数据
//        QVector<QString> matchResults = reTool.Match(data);
//        for(const QString& match : matchResults)
//        {
//            qDebug() << match;
//        }

        QVector<QString> matchResults = reTool.Match(data);

        bool isWriteOk = csvTool.WriteCSV(headers, matchResults, "utf-8");
        if(isWriteOk)
        {
            qDebug() << "Spyder info has been successfully written to CSV file.";
        }
        else
        {
            qDebug() << "Failed to written spyder info to CSV file.";
        }

        // read data from csv file
        QVector<QString> readData = csvTool.ReadCSV();
        // Compare original test data with the data read from the csv file
        if(matchResults == readData)
        {
            qDebug() << "Data read from the csv file match the original test data.";
        }
        else
        {
            qDebug() << "Data read from the csv file doesn't match the original test data.";
        }

        // exit the app
        QTimer::singleShot(0, &Exit);

    });

    // error handle
    QObject::connect(&httpAccess, &HttpAccess::error, [](const QString& errorString){
        qDebug() << errorString;

        QTimer::singleShot(0, &Exit);
    });

    httpAccess.Get(QUrl("https://www.baidu.com/"));

    return a.exec();
}
