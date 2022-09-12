# river-xmonadwm

# Build

```
git clone git@github.com:alex-courtis/river-xmonadwm.git
cd river-xmonadwm
meson build
ninja -C build
```

# Install

```
sudo ninja -C build install
```

# Man

```
meson --reconfigure build -Dman=enabled
ninja -C build
```
