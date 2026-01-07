#!/bin/bash

CHECK_ORIG_AKIM=$(git remote | grep -c 'origin-akim')
if [ "$CHECK_ORIG_AKIM" -eq 0 ]; then
	git remote add origin-akim "git@github.com:DanielAkim2000/minishell.git"
fi
CHECK_ORIG_REMI=$(git remote | grep -c 'origin-remi')
if [ "$CHEK_ORIG_REMI" -eq 0 ]; then
	git remote add origin-remi "git@github.com:alcorcamel/minishell.git"
fi
git push origin-akim
git push origin-remi