.PHONY: run pre 2023 2024 pre-2023 pre-2024

# read and export .env file(s)
ifneq (,$(wildcard ./.env))
    include .env
    export
endif

ifneq (,$(wildcard $(YEAR)/.env))
    include $(YEAR)/.env
    export
endif

SHELL := /bin/bash
CWD := $(WORKDIR)/$(YEAR)

run: pre $(YEAR)

pre:
	@if [ -z "$(YEAR)" ]; then \
	    	echo "YEAR is not set"; \
		exit 1; \
	fi
	export CWD=$(CWD)
	
# Python 3.10 check
pre-2023:
	@if [ -z "$(shell which python3)" ] && [ "$(shell python3 --version | cut -d '.' -f 2)" -eq 10 ]; then \
		echo "python3.10 not installed or used"; \
		exit 1; \
	fi

2023: pre-2023
	python3 2023/main.py

# Cmake (3.31.1 and C++23 determined by CMakelist)
pre-2024:
	@if [ -z "$(shell which cmake)" ]; then \
		echo "cmake not installed"; \
		exit 1; \
	fi

2024: pre-2024
	cmake -S 2024 -B 2024 && $(MAKE) -C 2024 --no-print-directory && ./2024/2024
	
