run:
	make ${YEAR} -B --no-print-directory

PYTHON := $(shell command -v python3 || command -v python || echo "not found")
PYTHON_VERSION := $(shell $(PYTHON) --version 2>/dev/null | awk '{print $$2}' || echo "0.0")
MINIMUM_PYTHON_VERSION := 3.10

2023:
ifeq ($(PYTHON), not found)
	@echo "Error: Python 3.10 is not found in PATH."; exit 1
endif
	@min_version=$(MINIMUM_PYTHON_VERSION); \
	current_version=$(PYTHON_VERSION); \
	if [ $$(echo "$$current_version $$min_version" | awk '{if ($$1 < $$2) print "yes"; else print "no"}') = "yes" ]; then \
		echo "Error: Python version $$min_version is required."; \
		exit 1; \
	fi

	python3 2023/main.py
