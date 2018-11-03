#!/bin/sh

# Delete docker contents

if [ -z "$1" ]
then
    echo "What do you want to delete ? 1 (containers), 2 (images), 3 (machines)"
else
    if [ "$1" == "1" ]
    then
        docker rm -f $(docker ps -a -q)
        echo "Deleted all containers."

    elif [ "$1" == "2" ]
    then
        docker rmi -f $(docker images -q)
        echo "Deleted all images"

    elif [ "$1" == "3" ]
    then
        docker-machine rm -f $(docker-machine ls -q)
        echo "Deleted all machines"

    else
        echo "Incorrect input. Type 1, 2 or 3"
    fi
fi
