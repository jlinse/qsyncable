#ifndef QSUUID_H
#define QSUUID_H

#include <QObject>

class QQmlEngine;
class QJSEngine;

class QSUuid : public QObject
{
    Q_OBJECT
public:
    explicit QSUuid(QObject *parent = 0);

    static QObject *qmlSingletonProvider(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
  public slots:

    QString create() const;

};

#endif // QSUUID_H
