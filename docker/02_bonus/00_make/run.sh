#!/bin/bash

ARGS=$@

export TERM=xterm

make $ARGS -C /src

