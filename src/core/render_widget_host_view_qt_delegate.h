/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#ifndef RENDER_WIDGET_HOST_VIEW_QT_DELEGATE_H
#define RENDER_WIDGET_HOST_VIEW_QT_DELEGATE_H

#include <QtWebEngineCore/private/qtwebenginecoreglobal_p.h>
#include <QtCore/QRect>
#include <QtGui/QColor>
#include <QtGui/QCursor>
#include <QtGui/QImage>

QT_BEGIN_NAMESPACE
class QWheelEvent;
class QWindow;
QT_END_NAMESPACE

namespace QtWebEngineCore {

class WebContentsAdapterClient;
class Q_WEBENGINECORE_PRIVATE_EXPORT RenderWidgetHostViewQtDelegate {
public:
    virtual ~RenderWidgetHostViewQtDelegate() { }
    virtual void initAsPopup(const QRect&) = 0;
    virtual QRectF viewGeometry() const = 0;
    virtual QRect windowGeometry() const = 0;
    virtual void setKeyboardFocus() = 0;
    virtual bool hasKeyboardFocus() = 0;
    virtual void lockMouse() = 0;
    virtual void unlockMouse() = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual bool isVisible() const = 0;
    virtual QWindow *Window() const = 0;
    virtual void updateCursor(const QCursor &) = 0;
    virtual void resize(int width, int height) = 0;
    virtual void move(const QPoint &) = 0;
    virtual void inputMethodStateChanged(bool editorVisible, bool passwordInput) = 0;
    virtual void setInputMethodHints(Qt::InputMethodHints hints) = 0;
    virtual void setClearColor(const QColor &color) = 0;
    virtual void adapterClientChanged(WebContentsAdapterClient *client) = 0;
    virtual void unhandledWheelEvent(QWheelEvent *) {}
};

} // namespace QtWebEngineCore

#endif // RENDER_WIDGET_HOST_VIEW_QT_DELEGATE_H
