#!/bin/sh

# if im-select already exist, delete it and download it again
if [ -e /usr/local/bin/im-select ]
then
    rm -f /usr/local/bin/im-select
fi

echo "* Downloading im-select..."

curl -Ls -o /usr/local/bin/im-select https://github.com/daipeihust/im-select/raw/master/im-select-mac/out/intel/im-select

chmod 777 /usr/local/bin/im-select

echo "* im-select is installed!"
echo "*"
echo "*"
echo "*"
echo "* now run \"im-select\" in your terminal!"
