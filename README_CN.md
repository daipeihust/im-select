# 概述

im-select可以让你从命令行切换输入法。这个项目是 [VSCodeVim](https://github.com/VSCodeVim/Vim) 的附属项目，VSCodeVim的自动切换输入法功能需要用到这个项目中的程序。

# 如何安装

## macOS

将下面一行复制到你的命令行中并运行：
```shell
curl -Ls https://raw.githubusercontent.com/daipeihust/im-select/master/install_mac.sh | sh
```
im-select程序会被下载到`/usr/local/bin/`路径。


### Apple Silicon 支持


点击[这里](https://github.com/daipeihust/im-select/blob/8080ad18f20218d1b6b5ef81d26cc5452d56b165/im-select-mac/out/apple/im-select)下载特殊的版本。

## windows

下载 [im-select.exe](https://github.com/daipeihust/im-select/raw/master/im-select-win/out/x86/im-select.exe)，然后把它移动到一个合适的路径。（如果你需要64位的版本，可以下载[这个](https://github.com/daipeihust/im-select/raw/master/im-select-win/out/x64/im-select.exe)）

## linux

Linux环境下你不需要下载im-select，因为Linux有许多命令行工具可以切换输入法。


# Usage

## macOS
如果你的 PATH 包含 `/usr/local/bin`，你可以直接使用 `im-select`。

### 获取当前使用的输入法
```shell
/usr/local/bin/im-select
```
### 切换输入法
```shell
/usr/local/bin/im-select imkey
```
举例： `/usr/local/bin/im-select com.apple.keylayout.US`

## linux

### ibus

[@mengbo](https://github.com/mengbo) 为 ibus 提供了如下配置：

```
"vim.autoSwitchInputMethod.enable": true,
"vim.autoSwitchInputMethod.defaultIM": "xkb:us::eng",
"vim.autoSwitchInputMethod.obtainIMCmd": "/usr/bin/ibus engine",
"vim.autoSwitchInputMethod.switchIMCmd": "/usr/bin/ibus engine {im}"
```

### xkb-switch

[@VEL4EG](https://github.com/VEL4EG) 为 xkb-switch 提供了如下配置：

```
"vim.autoSwitchInputMethod.enable": true,
"vim.autoSwitchInputMethod.defaultIM": "us",
"vim.autoSwitchInputMethod.obtainIMCmd": "/usr/local/bin/xkb-switch",
"vim.autoSwitchInputMethod.switchIMCmd": "/usr/local/bin/xkb-switch -s {im}"
```

### fcitx

[@yunhao94](https://github.com/yunhao94) 为 fcitx 提供了如下配置：

```
"vim.autoSwitchInputMethod.enable": true,
"vim.autoSwitchInputMethod.defaultIM": "1",
"vim.autoSwitchInputMethod.obtainIMCmd": "/usr/bin/fcitx-remote",
"vim.autoSwitchInputMethod.switchIMCmd": "/usr/bin/fcitx-remote -t {im}",
```
### gdbus

[@d-r-q](https://github.com/d-r-q) 为 gdbus 提供了如下配置：

Put `gdbus call --session --dest org.gnome.Shell --object-path /org/gnome/Shell --method org.gnome.Shell.Eval "imports.ui.status.keyboard.getInputSourceManager().currentSource.index" | awk -F'[^0-9]*' '{print $2}'` into get-im.sh.

Put `gdbus call --session --dest org.gnome.Shell --object-path /org/gnome/Shell --method org.gnome.Shell.Eval "imports.ui.status.keyboard.getInputSourceManager().inputSources[$1].activate()"` into set-im.sh.

```
"vim.autoSwitchInputMethod.enable": true,
"vim.autoSwitchInputMethod.defaultIM": "0",
"vim.autoSwitchInputMethod.obtainIMCmd": "<path to get-im.sh>",
"vim.autoSwitchInputMethod.switchIMCmd": "<path to set-im.sh> {im}",
```

## windows
在Windows环境下，im-select.exe 是一个命令行工具，但是不能在系统的 cmd 或者 powershell 中运行，这是微软的bug，键盘的 API 不支持这两个命令行，我推荐你使用 git-bash。

> 注意：git-bash 并不是必须的，只有你在 VSCodeVim 的配置过程中，不知道当前的输入法的key，你才需要这样去获取输入法的key。

### 获取当前输入法的key
```shell
/path/to/im-select.exe
```

### 切换输入法
```shell
/path/to/im-select.exe locale
```

> 注意：Windows系统的路径和Linux会有些不一样，类似这样: C:\Users\path\to\file
### windows-imm
详见 [select-im-imm](./win-imm/im-select-imm/README_CN.md) 提供切换同一输入法下中英文的能力

# 联系我

<div align="left">
    <img src="contact_me.jpeg" height="300">
    <img src="support_me.jpeg" height="300">
</div>
