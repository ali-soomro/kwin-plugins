#include "x11shadow.h"

#include <QGuiApplication>
#include <QtGui/qguiapplication_platform.h>
#include <xcb/xcb.h>
#include <cstring>

static xcb_atom_t internAtom(const char *name, bool only_if_exists)
{
    if (!name || *name == 0)
        return XCB_NONE;

    auto *x11app = qGuiApp->nativeInterface<QNativeInterface::QX11Application>();
    if (!x11app)
        return XCB_NONE;

    xcb_connection_t *conn = x11app->connection();
    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(conn, only_if_exists, strlen(name), name);
    xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(conn, cookie, nullptr);

    if (!reply)
        return XCB_NONE;

    xcb_atom_t atom = reply->atom;
    free(reply);

    return atom;
}

X11Shadow::X11Shadow(QObject *parent)
    : QObject(parent)
{
    m_atom_net_wm_shadow = internAtom("_KDE_NET_WM_SHADOW", false);
    m_atom_net_wm_window_type = internAtom("_NET_WM_WINDOW_TYPE", false);
}
