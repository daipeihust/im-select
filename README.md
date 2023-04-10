# Welcome to <%= im-select %> 👋
[![Version](https://img.shields.io/npm/v/<%= projectName %>.svg)(https://www.npmjs.com/package/<%= projectName %>)
![Prerequisite](https://img.shields.io/badge/<%= name %>-<%= encodeURIComponent(value) %>-blue.svg)
<% if (isGithubRepos) { -%>
[![Maintenance][(https://img.shields.io/badge/Maintained%3F-yes-green.svg)](<%= repositoryUrl %>/graphs/commit-activity)
<% } -%>
<% if (licenseName) { -%>
[![License: <%= licenseName %>](https://img.shields.io/<%= isGithubRepos ? `github/license/${authorGithubUsername}/${projectName}` : `badge/License-${licenseName}-yellow.svg` %>)](<%= licenseUrl ? licenseUrl : '#' %>)
<% } -%>

### 🏠 [Homepage](<%= projectHomepage %>)
<% if (projectDemoUrl) { -%>

### ✨ [Demo](<%= projectDemoUrl %>)
<% } -%>
<% if (projectPrerequisites && projectPrerequisites.length) { -%>

## Prerequisites

<% projectPrerequisites.map(({ name, value }) => { -%>
- <%= name %> <%= value %>
<% }) -%>
<% } -%>
<% if (installCommand) { -%>

## Install

### macOS

Run following command in your console:
```shell
curl -Ls https://raw.githubusercontent.com/daipeihust/im-select/master/install_mac.sh | sh
```
The im-select program will be downloaded to your `/usr/local/bin/` path.

#### Apple Silicon support

Click [here](https://github.com/daipeihust/im-select/blob/8080ad18f20218d1b6b5ef81d26cc5452d56b165/im-select-mac/out/apple/im-select) to download specific im-select program

### windows

Download the [im-select.exe](https://github.com/daipeihust/im-select/raw/master/im-select-win/out/x86/im-select.exe), and move it to the proper path.(If you need the 64 bit version, you can download [this one](https://github.com/daipeihust/im-select/raw/master/im-select-win/out/x64/im-select.exe).)

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
<% if (authorName) { %>
👤 **<%= authorName %>**
<% } %>
<% if (authorWebsite) { -%>
* Website: <%= authorWebsite %>
<% } -%>
<% if (authorTwitterUsername) { -%>
* Twitter: [@<%= authorTwitterUsername %>](https://twitter.com/<%= authorTwitterUsername %>)
<% } -%>
<% if (authorGithubUsername) { -%>
* GitHub: [@<%= authorGithubUsername %>](https://github.com/<%= authorGithubUsername %>)
<% } -%>
<% if (authorLinkedInUsername) { -%>
* LinkedIn: [@<%= authorLinkedInUsername %>](https://linkedin.com/in/<%= authorLinkedInUsername %>)
<% } -%>
<% } -%>
<% if (issuesUrl) { -%>

## 🤝 Contributing

Contributions, issues and feature requests are welcome!

Feel free to check [issues page](<%= issuesUrl %>). <%= contributingUrl ? `You can also take a look at the [contributing guide](${contributingUrl}).` : '' %>
<% } -%>

## Show your support

Give a ⭐️ if this project helped you!

<div align="left">
    <img src="contact_me.jpeg" height="300">
    <img src="support_me.jpeg" height="300">
</div>

## 📝 License



