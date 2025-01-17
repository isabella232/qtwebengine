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

#ifndef UI_DELEGATES_MANAGER_H
#define UI_DELEGATES_MANAGER_H

#include <QtCore/qcoreapplication.h>
#include <QtCore/qpoint.h>
#include <QtCore/qscopedpointer.h>
#include <QtCore/qsharedpointer.h>
#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>

#define FOR_EACH_COMPONENT_TYPE(F, SEPARATOR)                                                      \
    F(Menu, menu) SEPARATOR F(MenuItem, menuItem)                                                  \
    SEPARATOR                                                                                      \
    F(MenuSeparator, menuSeparator) SEPARATOR F(AlertDialog, alertDialog)                          \
    SEPARATOR                                                                                      \
    F(ColorDialog, colorDialog) SEPARATOR F(ConfirmDialog, confirmDialog)                          \
    SEPARATOR                                                                                      \
    F(PromptDialog, promptDialog) SEPARATOR F(FilePicker, filePicker)                              \
    SEPARATOR                                                                                      \
    F(AuthenticationDialog, authenticationDialog) SEPARATOR F(ToolTip, toolTip)                    \
    SEPARATOR                                                                                      \
    F(TouchHandle, touchHandle) SEPARATOR F(TouchSelectionMenu, touchSelectionMenu)                \
    SEPARATOR                                                                                      \
    F(AutofillPopup, autofillPopup) SEPARATOR

#define COMMA_SEPARATOR ,
#define SEMICOLON_SEPARATOR ;
#define ENUM_DECLARATION(TYPE, COMPONENT) \
    TYPE
#define MEMBER_DECLARATION(TYPE, COMPONENT) \
    QQmlComponent *COMPONENT##Component

QT_BEGIN_NAMESPACE
class QQmlComponent;
class QQmlContext;
class QQmlEngine;
class QQuickItem;
class QQuickWebEngineAction;
class QQuickWebEngineView;
QT_END_NAMESPACE

namespace QtWebEngineCore {
class AuthenticationDialogController;
class AutofillPopupController;
class ColorChooserController;
class FilePickerController;
class JavaScriptDialogController;
class TouchSelectionMenuController;

const char *defaultPropertyName(QObject *obj);

class UIDelegatesManager
{
    Q_DECLARE_TR_FUNCTIONS(UIDelegatesManager)
public:
    enum ComponentType {
        Invalid = -1,
        FOR_EACH_COMPONENT_TYPE(ENUM_DECLARATION, COMMA_SEPARATOR)
        ComponentTypeCount
    };

    UIDelegatesManager(QQuickWebEngineView *);
    virtual ~UIDelegatesManager();

    virtual bool initializeImportDirs(QStringList &dirs, QQmlEngine *engine);
    virtual void addMenuItem(QQuickWebEngineAction *action, QObject *menu,
                             bool checkable = false, bool checked = true);
    void addMenuSeparator(QObject *menu);
    virtual QObject *addMenu(QObject *parentMenu, const QString &title,
                             const QPoint &pos = QPoint());
    QQmlContext *creationContextForComponent(QQmlComponent *);
    void showColorDialog(QSharedPointer<ColorChooserController>);
    void showDialog(QSharedPointer<JavaScriptDialogController>);
    void showDialog(QSharedPointer<AuthenticationDialogController>);
    void showFilePicker(QSharedPointer<FilePickerController>);
    virtual void showMenu(QObject *menu);
    void showToolTip(const QString &text);
    QQuickItem *createTouchHandle();
    void showTouchSelectionMenu(TouchSelectionMenuController *, const QRect &, const int spacing);
    void hideTouchSelectionMenu();
    void showAutofillPopup(QtWebEngineCore::AutofillPopupController *controller, QPointF pos,
                           int width, bool autoselectFirstSuggestion);
    void hideAutofillPopup();

private:
    bool ensureComponentLoaded(ComponentType);

    QQuickWebEngineView *m_view;
    QStringList m_importDirs;
    QScopedPointer<QObject> m_toolTip;
    QScopedPointer<QObject> m_touchSelectionMenu;
    QScopedPointer<QObject> m_autofillPopup;

    FOR_EACH_COMPONENT_TYPE(MEMBER_DECLARATION, SEMICOLON_SEPARATOR)

    Q_DISABLE_COPY(UIDelegatesManager)

};

class AutofillPopupEventFilter : public QObject
{
    Q_OBJECT

public:
    AutofillPopupEventFilter(QtWebEngineCore::AutofillPopupController *controller,
                             UIDelegatesManager *manager, QObject *parent)
        : QObject(parent), m_controller(controller), m_manager(manager)
    {
    }

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    QtWebEngineCore::AutofillPopupController *m_controller;
    UIDelegatesManager *m_manager;
};

} // namespace QtWebEngineCore

#endif // UI_DELEGATES_MANAGER_H
