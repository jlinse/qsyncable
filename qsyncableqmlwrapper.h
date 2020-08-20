#ifndef QSYNCABLEQMLWRAPPER_H
#define QSYNCABLEQMLWRAPPER_H

#include <QObject>
#include <QJSValue>

class QQmlEngine;
class QJSEngine;

class QSyncableQmlWrapper : public QObject
{
    Q_OBJECT
public:
    explicit QSyncableQmlWrapper(QObject *parent = 0);

    static QObject *qmlSingletonProvider(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
signals:

public slots:

    void assign(QObject* dest, QJSValue source);

};

#endif // QSYNCABLEQMLWRAPPER_H
