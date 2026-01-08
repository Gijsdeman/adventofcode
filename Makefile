.PHONY: run pre 2022 2023 2024 2025 pre-2022 pre-2023 pre-2024 pre-2025

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
CWD := $(PWD)/$(YEAR)

run: pre $(YEAR)

pre:
	@if [ -z "$(YEAR)" ]; then \
	    	echo "YEAR is not set"; \
		exit 1; \
	fi
	export CWD=$(CWD)
	
# Go 1.25+ check
pre-2022:
	@if [ -z "$(shell which go)" ]; then \
		echo "go not installed"; \
		exit 1; \
	fi
	@MAJOR=$$(go version 2>/dev/null | sed -n 's/.*go\([0-9]*\)\.\([0-9]*\).*/\1/p'); \
	MINOR=$$(go version 2>/dev/null | sed -n 's/.*go\([0-9]*\)\.\([0-9]*\).*/\2/p'); \
	if [ "$$MAJOR" -lt 1 ] || ([ "$$MAJOR" -eq 1 ] && [ "$$MINOR" -lt 25 ]); then \
		echo "go version 1.25+ required (found version $$MAJOR.$$MINOR)"; \
		exit 1; \
	fi

2022: pre-2022
	cd 2022 && go run main.go

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

# dotnet 10 check
pre-2025:
	@if [ -z "$(shell which dotnet)" ]; then \
		echo "dotnet not installed"; \
		exit 1; \
	fi
	@MAJOR=$$(dotnet --version 2>/dev/null | cut -d '.' -f 1); \
	if [ "$$MAJOR" -ne 10 ]; then \
		echo "dotnet version 10 required (found version $$MAJOR)"; \
		exit 1; \
	fi

2025: pre-2025
	echo $(YEAR)
	echo $(CWD)
	cd 2025 && dotnet run --project 2025.csproj
	
