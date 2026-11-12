#include "datagenerator.h"

DataGenerator::DataGenerator(int intervalMilliseconds, Range range, int duration, int maxStep, QObject *parent)
    : QObject(parent), m_intervalMilliseconds(intervalMilliseconds), m_range(range),
    m_duration(duration), m_maxStep(maxStep),
    m_counter(0), m_currentValue(0)
{
    qDebug() << "DataGenerator initialization: ";
    qDebug() << "       interval:   " << m_intervalMilliseconds;
    qDebug() << "       low range:  " << m_range.low;
    qDebug() << "       high range: " << m_range.high;
    qDebug() << "       duration:   " << m_duration;
    qDebug() << "       max step:   " << m_maxStep;

    qDebug() << "numeric upper int limit" << std::numeric_limits<int>::max();
    qDebug() << "numeric lower int limit" << std::numeric_limits<int>::min();

    if (m_range.high > std::numeric_limits<int>::max()) {
        throw std::invalid_argument("Range high exceeds supported limit");
    }

    if (m_range.low < std::numeric_limits<int>::min()) {
        throw std::invalid_argument("Range low exceeds supported limit");
    }

    if (m_range.low > m_range.high) {
        throw std::invalid_argument("Range: low cannot be greater than high");
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
    // quint64 is used for QRandomGenerator requirements
    qint64 low  = m_range.low;
    qint64 high = m_range.high;

    if (m_counter != 0) {
        low  = qMax<qint64>(low,  static_cast<qint64>(m_currentValue) - m_maxStep);
        high = qMin<qint64>(high, static_cast<qint64>(m_currentValue) + m_maxStep);
    }

    const qint64 span = high - low + 1;

    qint64 value = low + static_cast<qint64>(QRandomGenerator::global()->bounded(static_cast<quint32>(span)));

    m_currentValue = static_cast<int>(value);
    qDebug() << m_counter << "draw: " << m_currentValue;
    m_counter++;

    if (m_counter >= m_duration) {
        m_timer.stop();
        m_counter = 0;
    }

    emit dataGenerated(m_currentValue);
}

