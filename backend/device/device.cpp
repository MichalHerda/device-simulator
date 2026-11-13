#include "device.h"

Device::Device(QObject *parent)
    : QObject{parent}
{}

int Device::id() const
{
    return m_id;
}

void Device::setId(int id)
{
    if(m_id == id) {
        return;
    }
    m_id = id;
    emit idChanged();
}

QString Device::name() const
{
    return m_name;
}

void Device::setName(const QString &name)
{
    if(m_name == name) {
        return;
    }
    m_name = name;
    emit nameChanged();
}

bool Device::infiniteDuration() const
{
    return m_infiniteDuration;
}

void Device::setInfiniteDuration(bool infiniteDuration)
{
    if(m_infiniteDuration == infiniteDuration) {
        return;
    }
    m_infiniteDuration == infiniteDuration;
    emit infiniteDurationChanged();
}

int Device::intervalMiliseconds() const
{
    return m_intervalMiliseconds;
}

void Device::setIntervalMiliseconds(int intervalMiliseconds)
{
    if(m_intervalMiliseconds == intervalMiliseconds) {
        return;
    }
    m_intervalMiliseconds == intervalMiliseconds;
    emit intervalMilisecondsChanged();
}

int Device::lowRange() const
{
    return m_range.low;
}

void Device::setLowRange(int lowRange)
{
    if(m_range.low == lowRange) {
        return;
    }
    m_range.low = lowRange;
}

int Device::highRange() const
{
    return m_range.high;
}

void Device::setHighRange(int highRange)
{
    if(m_range.high == highRange) {
        return;
    }
    m_range.high = highRange;
}

int Device::duration() const
{
    return m_duration;
}

void Device::setDuration(int duration)
{
    if(m_duration == duration) {
        return;
    }
    m_duration = duration;
}

int Device::maxStep() const
{
    return m_maxStep;
}

void Device::setMaxStep(int maxStep)
{
    if(m_maxStep == maxStep) {
        return;
    }
    m_maxStep = maxStep;
}

