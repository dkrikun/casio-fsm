#!/usr/bin/env bash

# download smc -- not necessary, already included in the codebase
# wget -O - http://sourceforge.net/projects/smc/files/smc/6_1_0/smc_6_1_0.tgz/download | tar -xz
# mv smc_6_1_0 foreign/smc_6_1_0


apt-get update

# set up git and vim -- not necessary, code editing & git takes place outside the vm
# apt-get install -y git
# apt-get install -y vim
# 
# git config --global core.editor vim
# git config --global color.ui = true

apt-get install -y openjdk-6-jre graphviz libncurses5 libncurses5-dev make g++ \
	libboost-program-options1.48.0 libboost-program-options1.48-dev \
	libboost-chrono1.48 libboost-chrono1.48-dev \
	libboost-system1.48 libboost-system1.48-dev
