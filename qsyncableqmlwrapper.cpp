#include "qsyncablefunctions.h"
#include "qsyncableqmlwrapper.h"

QSyncableQmlWrapper::QSyncableQmlWrapper(QObject *parent) : QObject(parent)
{

}

QObject *QSyncableQmlWrapper::qmlSingletonProvider(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
  Q_UNUSED (qmlEngine)
  Q_UNUSED (jsEngine)
  return new QSyncableQmlWrapper;
}

void QSyncableQmlWrapper::assign(QObject *dest, QJSValue source)
{
    return QSyncable::assign(dest, source);
}
