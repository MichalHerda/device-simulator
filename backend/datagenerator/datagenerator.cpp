#include "datagenerator.h"

DataGenerator::DataGenerator(int interval, Range range, int duration, int maxStep, QObject *parent)
    : m_interval(interval), m_range(range), m_duration(duration), m_maxStep(maxStep), QObject{parent}
{
    qDebug() << "DataGenerator initialization: ";
    qDebug() << "       interval:   ", m_interval;
    qDebug() << "       low range:  ", m_range.low;
    qDebug() << "       high range: ", m_range.high;
    qDebug() << "       duration:   ", m_duration;
    qDebug() << "       max step:   ", m_maxStep;

    m_timer.setInterval(m_interval);
    connect(&m_timer, &QTimer::timeout, this, &DataGenerator::onTimeout);
    m_timer.start();
}

void DataGenerator::onTimeout()
{
    qDebug() << "on timeout: " << m_counter;
    m_counter++;

    if(m_counter >= m_duration) {
        m_timer.stop();
        m_counter = 0;
    }
}
