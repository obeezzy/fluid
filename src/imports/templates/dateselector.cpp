/*
 * This file is part of Fluid.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:MPL2$
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * $END_LICENSE$
 */

#include "dateselector.h"

DateSelector::DateSelector(QQuickItem *parent)
    : QQuickItem(parent)
    , m_contentItem(new QQuickItem(this))
    , m_from(QDate(1, 1, 1))
    , m_to(QDate(275759, 9, 25))
    , m_selectedDate(QDate::currentDate())
{
    m_contentItem->setParentItem(this);

    connect(this, &QQuickItem::widthChanged, this, &DateSelector::updateLayout);
    connect(this, &QQuickItem::heightChanged, this, &DateSelector::updateLayout);
}

QLocale DateSelector::locale() const
{
    return m_locale;
}

void DateSelector::setLocale(const QLocale &locale)
{
    if (m_locale == locale)
        return;

    m_locale = locale;
    Q_EMIT localeChanged();
}

QQuickItem *DateSelector::contentItem() const
{
    return m_contentItem;
}

QQuickItem *DateSelector::navigator() const
{
    return m_navigator;
}

void DateSelector::setNavigator(QQuickItem *item)
{
    if (m_navigator == item)
        return;

    if (m_navigator)
        m_navigator->setParentItem(nullptr);

    m_navigator = item;
    m_navigator->setParentItem(m_contentItem);
    updateLayout();
    Q_EMIT navigatorChanged();
}

QQuickItem *DateSelector::calendar() const
{
    return m_calendar;
}

void DateSelector::setCalendar(QQuickItem *item)
{
    if (m_calendar == item)
        return;

    if (m_calendar)
        m_calendar->setParentItem(nullptr);

    m_calendar = item;
    m_calendar->setParentItem(m_contentItem);
    updateLayout();
    Q_EMIT calendarChanged();
}

bool DateSelector::dayOfWeekRowVisible() const
{
    return m_dayOfWeekRowVisible;
}

void DateSelector::setDayOfWeekRowVisible(bool value)
{
    if (m_dayOfWeekRowVisible == value)
        return;

    m_dayOfWeekRowVisible = value;
    Q_EMIT dayOfWeekRowVisibleChanged();
}

void DateSelector::resetDayOfWeekRowVisible()
{
    setDayOfWeekRowVisible(true);
}

bool DateSelector::weekNumberVisible() const
{
    return m_weekNumberVisible;
}

void DateSelector::setWeekNumberVisible(bool value)
{
    if (m_weekNumberVisible == value)
        return;

    m_weekNumberVisible = value;
    Q_EMIT weekNumberVisibleChanged();
}

void DateSelector::resetWeekNumberVisible()
{
    setWeekNumberVisible(true);
}

QDateTime DateSelector::from() const
{
    return m_from;
}

void DateSelector::setFrom(const QDateTime &date)
{
    if (m_from == date)
        return;

    m_from = date;
    Q_EMIT fromChanged();
}

void DateSelector::resetFrom()
{
    setFrom(QDateTime(QDate(1, 1, 1)));
}

QDateTime DateSelector::to() const
{
    return QDateTime(m_to.date());
}

void DateSelector::setTo(const QDateTime &date)
{
    if (m_to.date() == date.date())
        return;

    m_to = date;
    Q_EMIT toChanged();
}

void DateSelector::resetTo()
{
    setTo(QDateTime(QDate(275759, 9, 25)));
}

QDateTime DateSelector::selectedDate() const
{
    return QDateTime(m_selectedDate.date());
}

void DateSelector::setSelectedDate(const QDateTime &date)
{
    if (m_selectedDate.date() == date.date())
        return;

    m_selectedDate = date;
    Q_EMIT selectedDateChanged();
}

void DateSelector::updateLayout()
{
    if (!m_contentItem || !m_navigator || !m_calendar)
        return;

    m_contentItem->setWidth(width());
    m_contentItem->setHeight(height());
    m_navigator->setWidth(width());
    m_navigator->setHeight(50);
    m_calendar->setWidth(width());
    m_calendar->setHeight(height() - m_navigator->height());
    m_calendar->setX(0);
    m_calendar->setY(m_navigator->height());
}
