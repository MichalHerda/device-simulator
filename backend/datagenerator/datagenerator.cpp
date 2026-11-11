#include "datagenerator.h"

DataGenerator::DataGenerator(int intervalMilliseconds, Range range, int duration, int maxStep, QObject *parent)
    : QObject(parent), m_intervalMilliseconds(intervalMilliseconds), m_range(range),
    m_duration(duration), m_maxStep(maxStep),
    m_counter(0), m_currentValue(0)
{
    qDebug() << "DataGenerator initialization: ";
    qDebug() << "       interval:   ", m_intervalMilliseconds;
    qDebug() << "       low range:  ", m_range.low;
    qDebug() << "       high range: ", m_range.high;
    qDebug() << "       duration:   ", m_duration;
    qDebug() << "       max step:   ", m_maxStep;

    if (m_range.low > m_range.high) {
        throw std::invalid_argument("Range: low cannot be greater than high");
    }

    if (m_range.high == std::numeric_limits<int>::max()) {
        throw std::invalid_argument("Range high exceeds supported limit");
    }

    if (m_intervalMilliseconds <= 0) {
        throw std::invalid_argument("Interval must be positive");
    }

    if (m_duration <= 0) {
        throw std::invalid_argument("Duration must be positive");
    }

    if (m_maxStep < 0) {
        throw std::invalid_argument("MaxStep cannot be negative");
    }

    connect(&m_timer, &QTimer::timeout, this, &DataGenerator::generateData);
    m_timer.setInterval(m_intervalMilliseconds);
    start();
}

void DataGenerator::start()
{
    if(!m_timer.isActive()) {
        m_timer.start();
    }
    else {
        qDebug() << "timer is running - the device starting unavailable";
    }
}

void DataGenerator::stop()
{
    if(m_timer.isActive()) {
        m_timer.stop();
    }
    else {
        qDebug() << "timer is not running - the device stopping unavailable";
    }
}

void DataGenerator::generateData()
{
    int low;
    int high;

    if(m_counter == 0) {
        low = m_range.low;
        high = m_range.high;
    }
    else {
        low = qMax(m_range.low, m_currentValue - m_maxStep);
        high = qMin(m_range.high, m_currentValue + m_maxStep);
    }
    m_currentValue = QRandomGenerator::global()->bounded(low, high + 1);
    qDebug() << m_counter << ", draw: " << m_currentValue;
    m_counter++;

    if(m_counter >= m_duration) {
        m_timer.stop();
        m_counter = 0;
    }

    emit dataGenerated(m_currentValue);
}
