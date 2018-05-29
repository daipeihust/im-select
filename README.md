# im-select
Switch your input method from terminal. This project is a basic support for [VSCodeVim](https://github.com/VSCodeVim/Vim). It provides the command line program for VSCodeVim's autoSwitchIM function

# Installation

## macOS
Run following command in your terminal:
```shell
curl -Ls https://raw.githubusercontent.com/daipeihust/im-select/master/install_mac.sh | sh
```
The im-select program will be downloaded to your `/usr/local/bin/` path.
## windows

[Click here](https://github.com/daipeihust/im-select/raw/master/im-select-win/out/x86/im-select.exe) to download the im-select.exe, and move it to the proper path.

## linux
coming soon

# Usage

## macOS
### To get current input method key
```shell
/usr/local/bin/im-select
```
### To switch current input method
```shell
/usr/local/bin/im-select imkey
```
For example `/usr/local/bin/im-select com.apple.keylayout.US`
## windows
The im-select.exe is command line program, but it can't work in cmd or powershell. It's microsoft's fault, the keyboard API doesn't support in cmd and powershell. I recommend you [babun](http://babun.github.io/), an open source windows shell.

### To get current keyboard locale
```shell
/path/to/im-select.exe
```

### To switch current keyboard locale
```shell
/path/to/im-select.exe locale
```

> Note: 