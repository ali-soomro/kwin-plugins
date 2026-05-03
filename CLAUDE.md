# kwin-plugins — Cutefish KWin Plugins & Effects

## Purpose
KWin decoration plugins, window effects, scripts, and tabbox themes for Cutefish desktop integration with KDE Plasma 6.

## Build
```bash
cmake -B build -DCMAKE_INSTALL_PREFIX=/usr && cmake --build build && sudo cmake --install build
```

## Dependencies
- Qt6 (Core, Gui, Widgets)
- KDE Frameworks 6 (KF6Config, KF6ConfigGui, KF6CoreAddons, KF6WindowSystem)
- KDecoration3 (Plasma 6)
- C++20 required (for `operator<=>` in KDecoration3 headers)

## Structure

### plugins/decoration/ (cutefishdecoration)
- `decoration.cpp/h` — window decoration
- `button.cpp/h` — titlebar buttons
- `x11shadow.cpp/h` — X11 shadow handling
- `resources.qrc` — assets
- `cutefishos.json` — plugin metadata
- Installs `libcutefishdecoration.so` to `${QT_PLUGINS_DIR}/org.kde.kdecoration3/`

### plugins/roundedwindow/ — SKIPPED
- Uses removed KWin 6 APIs (`KWin::connection()`, `data.shader`)
- Would need rewrite using `OffscreenEffect` in KWin 6

### scripts/ (KWin JavaScript scripts)
- `cutefishlauncher/` — forces launcher window to stay in screen area
- `cutefish_squash/` — squash minimize animation (from Vlad Zahorodnii)
- `cutefish_scale/` — scale open/close animation
- `cutefish_popups/` — fading popups effect

### tabbox/
- `cutefish_thumbnail/` — thumbnail grid window switcher (QML, from Zren)

### config/
- `kglobalshortcutsrc`, `kwinrc`, `kwinrulesrc` — default KWin configuration

## Install Targets
- Decoration plugin → `${QT_PLUGINS_DIR}/org.kde.kdecoration3/`
- Config files → `/etc/xdg/`
- Scripts → `/usr/share/kwin/scripts/`
- Effects → `/usr/share/kwin/effects/`
- Tabbox → `/usr/share/kwin/tabbox/`

## KDecoration2→KDecoration3 Migration Notes
- `KDecoration2` namespace → `KDecoration3`
- `#include <KDecoration2/...>` → `#include <kdecoration3/....h>` (lowercase)
- `client()` → `window()` (DecoratedClient → DecoratedWindow)
- `init()` returns `bool` (was `void`)
- `settings()` returns `std::shared_ptr<DecorationSettings>` (was `QSharedPointer`)
- `setShadow(QSharedPointer)` → `setShadow(std::shared_ptr)`
- `QRect`/`QMargins` → `QRectF`/`QMarginsF`
- Plugin install dir: `org.kde.kdecoration2` → `org.kde.kdecoration3`
- JSON `ServiceTypes`: `kdecoration2` → `kdecoration3`
- C++20 required

## Status
✅ Ported, built, installed, pushed (github.com/ali-soomro). Rounded window effect skipped (KWin 6 GL API incompatible).
