#!/bin/bash

# Dockerenv script will install and run docker packages

if [ $USER != "root" ]; then
  echo "Run this script as root"
fi

echo -n "Setting up Docker apt repository: "
apt-get update 2>&1 >/dev/null
apt-get -y install apt-transport-https ca-certificates curl software-properties-common 2>&1 >/dev/null
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add - 2>&1 >/dev/null
add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" 2>&1 >/dev/null
echo "DONE"

echo -n "Installing Docker CE packages: "
apt-get update 2>&1 >/dev/null
apt-get -y install docker-ce
