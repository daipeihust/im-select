#!/bin/zsh

# 提交commit
git add --all
git commit -am "change file $*"

# 拉取远端代码
git pull --rebase

# 推送commit到远端仓库
git push
