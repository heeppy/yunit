/*
 * Copyright (C) 2015 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIRSURFACEITEM_H
#define MIRSURFACEITEM_H

#include "MirSurfaceItemModel.h"

#include <QQuickItem>
#include <QUrl>

class Session;

class MirSurfaceItem : public QQuickItem
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(State)
    Q_ENUMS(OrientationAngle)

    Q_PROPERTY(Type type READ type NOTIFY typeChanged)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(bool live READ live NOTIFY liveChanged)
    Q_PROPERTY(OrientationAngle orientationAngle READ orientationAngle WRITE setOrientationAngle
               NOTIFY orientationAngleChanged DESIGNABLE false)

public:
    enum Type {
        Normal,
        Utility,
        Dialog,
        Overlay,
        Freestyle,
        Popover,
        InputMethod,
    };

    enum State {
        Unknown,
        Restored,
        Minimized,
        Maximized,
        VertMaximized,
        /* SemiMaximized, */
        Fullscreen,
    };

    enum OrientationAngle {
        Angle0 = 0,
        Angle90 = 90,
        Angle180 = 180,
        Angle270 = 270
    };

    ~MirSurfaceItem();

    //getters
    Session* session() const { return m_session; }
    Type type() const { return m_type; }
    State state() const { return m_state; }
    QString name() const { return m_name; }
    bool live() const { return m_live; }
    OrientationAngle orientationAngle() const { return m_orientationAngle; }

    void setOrientationAngle(OrientationAngle angle);

    void setSession(Session* item);
    void setScreenshot(const QUrl& screenshot);
    void setLive(bool live);

    Q_INVOKABLE void setState(State newState);
    Q_INVOKABLE void release();

Q_SIGNALS:
    void typeChanged(Type);
    void stateChanged(State);
    void liveChanged(bool live);
    void orientationAngleChanged(OrientationAngle angle);

    // internal mock use
    void deregister();

protected:
    explicit MirSurfaceItem(const QString& name,
                            Type type,
                            State state,
                            const QUrl& screenshot,
                            const QString &qmlFilePath = QString(),
                            QQuickItem *parent = 0);

private Q_SLOTS:
    void onComponentStatusChanged(QQmlComponent::Status status);

private:
    void createQmlContentItem();
    void printComponentErrors();

    Session* m_session;
    const QString m_name;
    const Type m_type;
    State m_state;
    bool m_live;
    OrientationAngle  m_orientationAngle;

    QQmlComponent *m_qmlContentComponent;
    QQuickItem *m_qmlItem;
    QUrl m_screenshotUrl;

    friend class SurfaceManager;
};

Q_DECLARE_METATYPE(MirSurfaceItem*)
Q_DECLARE_METATYPE(QList<MirSurfaceItem*>)
Q_DECLARE_METATYPE(MirSurfaceItem::OrientationAngle)

#endif // MIRSURFACEITEM_H
