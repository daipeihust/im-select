#!/bin/zsh

git add --all
git commit -am "change file $*"

git pull --rebase

git push
