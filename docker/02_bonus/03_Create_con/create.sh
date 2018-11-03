#!/bin/bash

#    Script to create and set up a docker machine with the name given in param
#    "source createcon <name>" to properly eval while creating the container

if [ -z "$1" ]
then
    echo "You must name the container."
else
    docker-machine create -d virtualbox $1
    eval $(docker-machine env $1)
    echo "*hacker voice* I'm in."
fi
