#!/bin/bash

VENV_PATH="$HOME/venv/bin/activate"

cd $HOME
python3 -m venv venv
source $VENV_PATH
cd ~/projects/42_minishell
make re
python3 test.py
