# Welcome to **im-select** 👋


![image](https://user-images.githubusercontent.com/13344830/232276894-f84ee7d9-091e-40dd-8ad4-0b8840456a58.png)



<div align="center">
Switch your input method in shell. This project is a basic support for VSCodeVim. It provides the command line program for VSCodeVim's autoSwitchIM function.   

&nbsp;

![](https://img.shields.io/badge/Author-daipeihust-blue)
![GitHub repo size](https://img.shields.io/github/repo-size/daipeihust/im-select)
![GitHub repo file count](https://img.shields.io/github/directory-file-count/daipeihust/im-select)
![GitHub release (by tag)](https://img.shields.io/github/downloads/daipeihust/im-select/1.0.1/total)
![GitHub issues](https://img.shields.io/github/issues/daipeihust/im-select)
![GitHub](https://img.shields.io/github/license/daipeihust/im-select)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/daipeihust/im-select)
![GitHub commit activity](https://img.shields.io/github/commit-activity/y/daipeihust/im-select)
![GitHub contributors](https://img.shields.io/github/contributors/daipeihust/im-select)
![GitHub last commit](https://img.shields.io/github/last-commit/daipeihust/im-select)
![GitHub Discussions](https://img.shields.io/github/discussions/daipeihust/im-select)
![GitHub Repo stars](https://img.shields.io/github/stars/daipeihust/im-select?style=social)

</div>

&nbsp;

[English](./README.md) | [简体中文](./README_CN.md)


## Prerequisites

- using [VSCodeVim](https://github.com/VSCodeVim/Vim)
- have a Mac/Windows/Linux device
- download [git-bash](https://gitforwindows.org/)(if you on windows)
- know how to use [shell](https://zh.wikipedia.org/wiki/Unix_shell)

## Install

### macOS

#### Homebrew

```shell
brew tap daipeihust/tap
brew install im-select
```

Or you can run following command in your console:

```shell
curl -Ls https://raw.githubusercontent.com/daipeihust/im-select/master/install_mac.sh | sh
```

The im-select program will be downloaded to your `/usr/local/bin/` path.

### windows

Download the [im-select.exe](https://github.com/daipeihust/im-select/raw/master/win/out/x86/im-select.exe), and move it to the proper path.(If you need the 64 bit version, you can download [this one](https://github.com/daipeihust/im-select/raw/master/win/out/x64/im-select.exe).)

### linux

You don't have to install this for linux. linux have tools to switch input methods

## Usage

## macOS
If your PATH contains `/usr/local/bin`, you can just use `im-select` instead of `/usr/local/bin/im-select`
### To get current input method key
```shell
/usr/local/bin/im-select
```
### To switch current input method
```shell
/usr/local/bin/im-select imkey
```
For example `/usr/local/bin/im-select com.apple.keylayout.US`

## linux

### ibus

[@mengbo](https://github.com/mengbo) provided this configuration for ibus

```
"vim.autoSwitchInputMethod.enable": true,
"vim.autoSwitchInputMethod.defaultIM": "xkb:us::eng",
"vim.autoSwitchInputMethod.obtainIMCmd": "/usr/bin/ibus engine",
"vim.autoSwitchInputMethod.switchIMCmd": "/usr/bin/ibus engine {im}"
```

### xkb-switch

[@VEL4EG](https://github.com/VEL4EG) provided this configuration for xkb-switch

```
"vim.autoSwitchInputMethod.enable": true,
"vim.autoSwitchInputMethod.defaultIM": "us",
"vim.autoSwitchInputMethod.obtainIMCmd": "/usr/local/bin/xkb-switch",
"vim.autoSwitchInputMethod.switchIMCmd": "/usr/local/bin/xkb-switch -s {im}"
```

### fcitx

[@yunhao94](https://github.com/yunhao94) provided this configuration for fcitx

```
"vim.autoSwitchInputMethod.enable": true,
"vim.autoSwitchInputMethod.defaultIM": "1",
"vim.autoSwitchInputMethod.obtainIMCmd": "/usr/bin/fcitx-remote",
"vim.autoSwitchInputMethod.switchIMCmd": "/usr/bin/fcitx-remote -t {im}",
```

### gdbus

[@d-r-q](https://github.com/d-r-q) provide this configuration for gdbus

Put `gdbus call --session --dest org.gnome.Shell --object-path /org/gnome/Shell --method org.gnome.Shell.Eval "imports.ui.status.keyboard.getInputSourceManager().currentSource.index" | awk -F'[^0-9]*' '{print $2}'` into get-im.sh.

Put `gdbus call --session --dest org.gnome.Shell --object-path /org/gnome/Shell --method org.gnome.Shell.Eval "imports.ui.status.keyboard.getInputSourceManager().inputSources[$1].activate()"` into set-im.sh.

```
"vim.autoSwitchInputMethod.enable": true,
"vim.autoSwitchInputMethod.defaultIM": "0",
"vim.autoSwitchInputMethod.obtainIMCmd": "<path to get-im.sh>",
"vim.autoSwitchInputMethod.switchIMCmd": "<path to set-im.sh> {im}",
```

### qdbus (KDE)

[@igorechek06](https://igorek.dev) provided this configuration for qdbus

```
"vim.autoSwitchInputMethod.enable": true,
"vim.autoSwitchInputMethod.defaultIM": "0",
"vim.autoSwitchInputMethod.obtainIMCmd": "/usr/bin/qdbus org.kde.keyboard /Layouts getLayout",
"vim.autoSwitchInputMethod.switchIMCmd": "/usr/bin/qdbus org.kde.keyboard /Layouts setLayout {im}",
```

## windows
The im-select.exe is command line program, but it can't work in cmd or powershell. It's microsoft's bug, the keyboard API doesn't support in cmd and powershell. I recommend you git-bash.

> Note: The git-bash is not required. It's only used to get current input method key, which needed in VSCodeVim's configuration.

## Run tests

### To get current keyboard locale

```shell
/path/to/im-select.exe
```

### To switch current keyboard locale

```shell
/path/to/im-select.exe locale
```

> Note: The path in windows is like: C:\Users\path\to\file

## Author

<a href="https://github.com/daipeihust"><img width='50px' height='50px' src="https://avatars.githubusercontent.com/u/13344830?&v=4"></a>
<a href="https://github.com/liwanwhu"><img width='50px' height='50px' src="https://avatars.githubusercontent.com/u/22877659?v=4"></a> 
 

## 🤝 Contributing

If you find some issues, welcome to create pull request!

## Show your support

Give a ⭐️ if this project helped you!

Buy me a coffee, if you like it! If you have any problems, you can contact me via email!

<div align="left">
    <img src="contact_me.jpeg" height="300">
    <img src="support_me.jpeg" height="300">
</div>

## 📝 License

This project is licensed under the terms of the MIT license.

