#!/bin/bash

source .py3/bin/activate
black -t py39 $1
exit 0

