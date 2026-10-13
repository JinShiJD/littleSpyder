#include "retool.h"


QVector<QString> RETool::Match(const QString& input) const
{
    QVector<QString> result;
    QRegularExpression regex(m_pattern);
    QRegularExpressionMatchIterator i = regex.globalMatch(input);
    while(i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        //QString matchedInfo = match.captured(2) + ":" + match.captured(1);
        //qDebug() << "Matched: " << matchedInfo;
        result.append(match.captured(2) + " : " + match.captured(1));
    }

    return result;  // RVO
}
