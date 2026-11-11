#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMinMax>

#include <stdexcept>
#include <limits>

class DataGenerator : public QObject
{
    Q_OBJECT

public:
    struct Range
    {
        int low;
        int high;
    };

    explicit DataGenerator(int intervalMilliseconds, Range range, int duration,
                           int maxStep, QObject *parent = nullptr);

public slots:
    void start();
    void stop();

private slots:
    void generateData();

private:
    int m_intervalMilliseconds;
    Range m_range;
    int m_duration;
    int m_maxStep;

    QTimer m_timer;
    int m_counter;
    int m_currentValue;

signals:
    void dataGenerated(int value);
};

#endif // DATAGENERATOR_H
