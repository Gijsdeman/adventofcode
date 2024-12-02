SHELL := /bin/bash

run:
	make ${YEAR} -B --no-print-directory
2023:
	# Python 3.10 
	python3 2023/main.py
2024:
	# Cmake 3.31.1
	cd 2024 && source .env && cmake . && cmake --build . && SESSION=${SESSION} CWD=${CWD} ./2024
	
