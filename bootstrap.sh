#!/usr/bin/env bash

# download smc -- not necessary, already included in the codebase
# wget -O - http://sourceforge.net/projects/smc/files/smc/6_1_0/smc_6_1_0.tgz/download | tar -xz
# mv smc_6_1_0 foreign/smc_6_1_0


# set up git and vim
apt-get update

apt-get install -y git
apt-get install -y vim

git config --global core.editor vim
git config --global color.ui = true
