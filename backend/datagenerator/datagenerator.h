#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>

class DataGenerator : public QObject
{
    Q_OBJECT

public:
    struct Range
    {
        int low;
        int high;
    };

    explicit DataGenerator(int interval, Range range, int duration, int maxStep, QObject *parent = nullptr);

public slots:
    void onTimeout();

private:
    int m_interval;
    Range m_range;
    int m_duration;
    int m_maxStep;

    QTimer m_timer;
    int m_counter;

signals:
    void dataGenerated(int value);
};

#endif // DATAGENERATOR_H
