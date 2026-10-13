#include "httpaccess.h"

HttpAccess::HttpAccess(QObject *parent) : QObject(parent)
{

}

HttpAccess:: ~HttpAccess() {}

void HttpAccess::Get(const QUrl& url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager.get(request);

//    connect(reply, &QNetworkReply::finished, [&](){
//       if(reply->error() == QNetworkReply::NoError)
//       {
//            QByteArray data = reply->readAll();
//            emit finished(data);
//     }
//  });
    connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            // TODO: convert the html code
            QString htmlContent = QString::fromUtf8(data);
            emit finished(data);
        }
        else
        {
            emit error(reply->errorString());
        }
    });

}
