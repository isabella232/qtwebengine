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

#ifndef RENDER_WIDGET_HOST_VIEW_QT_DELEGATE_QUICKWINDOW_H
#define RENDER_WIDGET_HOST_VIEW_QT_DELEGATE_QUICKWINDOW_H

#include "render_widget_host_view_qt_delegate.h"
#include "render_widget_host_view_qt_delegate_item.h"

#include <QtCore/qpointer.h>
#include <QtQuick/qquickwindow.h>

namespace QtWebEngineCore {

class RenderWidgetHostViewQtDelegateQuickWindow : public QQuickWindow , public WidgetDelegate {

public:
    RenderWidgetHostViewQtDelegateQuickWindow(RenderWidgetHostViewQtDelegateItem *realDelegate,
                                              QWindow *parent);
    ~RenderWidgetHostViewQtDelegateQuickWindow();

    void InitAsPopup(const QRect &screenRect) override;
    void SetClearColor(const QColor &) override;
    bool ActiveFocusOnPress() override;
    void MoveWindow(const QPoint &) override;
    void Bind(WebContentsAdapterClient *) override;
    void Unbind() override;
    void Destroy() override;
    void Resize(int width, int height) override;

    void setVirtualParent(QQuickItem *virtualParent);

private:
    QPointer<RenderWidgetHostViewQtDelegateItem> m_realDelegate;
    QQuickItem *m_virtualParent;
    QRect m_rect;
    bool m_rotated;
};

} // namespace QtWebEngineCore

#endif // RENDER_WIDGET_HOST_VIEW_QT_DELEGATE_QUICKWINDOW_H
