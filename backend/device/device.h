#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QQmlEngine>
#include <QtQmlIntegration/qqmlintegration.h>

#include "backend/datagenerator/datagenerator.h"

class Device : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int id                  READ id                   WRITE setId                   NOTIFY idChanged                  )
    Q_PROPERTY(QString name            READ name                 WRITE setName                 NOTIFY nameChanged                )
    Q_PROPERTY(bool infiniteDuration   READ infiniteDuration     WRITE setInfiniteDuration     NOTIFY infiniteDurationChanged    )
    Q_PROPERTY(int intervalMiliseconds READ intervalMiliseconds  WRITE setIntervalMiliseconds  NOTIFY intervalMilisecondsChanged )
    Q_PROPERTY(int lowRange            READ lowRange             WRITE setLowRange             NOTIFY lowRangeChanged            )
    Q_PROPERTY(int highRange           READ highRange            WRITE setHighRange            NOTIFY highRangeChanged           )
    Q_PROPERTY(int duration            READ duration             WRITE setDuration             NOTIFY durationChanged            )
    Q_PROPERTY(int maxStep             READ maxStep              WRITE setMaxStep              NOTIFY maxStepChanged             )

public:
    explicit Device(QObject *parent = nullptr);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    bool infiniteDuration() const;
    void setInfiniteDuration(bool infiniteDuration);

    int intervalMiliseconds() const;
    void setIntervalMiliseconds(int intervalMiliseconds);

    int lowRange() const;
    void setLowRange(int lowRange);

    int highRange() const;
    void setHighRange(int highRange);

    int duration() const;
    void setDuration(int duration);

    int maxStep() const;
    void setMaxStep(int maxStep);

private:
    int m_id;
    QString m_name;
    bool m_infiniteDuration;

    int m_intervalMiliseconds;
    DataGenerator::Range m_range;
    int m_duration;
    int m_maxStep;

signals:
    void idChanged();
    void nameChanged();
    void infiniteDurationChanged();
    void intervalMilisecondsChanged();
    void lowRangeChanged();
    void highRangeChanged();
    void durationChanged();
    void maxStepChanged();

};

#endif // DEVICE_H
