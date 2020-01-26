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

#include "yearmodel.h"

YearModel::YearModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_from(QDate(1, 1, 1))
    , m_to(QDate(275759, 9, 25))
{
}

QDateTime YearModel::from() const
{
    return QDateTime(m_from.date());
}

void YearModel::setFrom(const QDateTime &date)
{
    if (m_from.date() == date.date())
        return;

    m_from = date;
    Q_EMIT fromChanged();
}

QDateTime YearModel::to() const
{
    return m_to;
}

void YearModel::setTo(const QDateTime &date)
{
    if (m_to.date() == date.date())
        return;

    m_to = date;
    Q_EMIT toChanged();
}

QHash<int, QByteArray> YearModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names.insert(Qt::DisplayRole, QByteArrayLiteral("year"));
    return names;
}

QVariant YearModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);

    if (!index.isValid())
        return QVariant();

    return m_list.at(index.row());
}

int YearModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.count();
}

int YearModel::get(int index) const
{
    if (index < 0 || index >= m_list.size())
        return -1;
    return m_list.at(index);
}

void YearModel::reset()
{
    beginResetModel();

    m_list.clear();

    if (m_from < m_to) {
        for (int i = m_from.date().year(); i < m_to.date().year(); i++)
            m_list.append(i);
    }

    endResetModel();
}
