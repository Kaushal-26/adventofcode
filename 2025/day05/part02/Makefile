.DEFAULT_GOAL := all

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++23 -DKaushal_26 -Wall -Wextra -Wno-unused-result -fconcepts -g -O2 -D_GLIBCXX_DEBUG -I ~/CP/libs/

# ANSI color codes
BLUE := $(shell tput -Txterm setaf 6)
GREEN := $(shell tput -Txterm setaf 2)
RED := $(shell tput -Txterm setaf 1)
YELLOW := $(shell tput -Txterm setaf 3)
CYAN := $(shell tput -Txterm setaf 6)
PURPLE := $(shell tput -Txterm setaf 5)
RESET := $(shell tput -Txterm sgr0) # No Color

# Automatically detect the single .cpp file in the root directory
SRC := $(wildcard *.cpp)
ifeq ($(SRC),)
    $(error No .cpp file found in current directory)
endif
ifneq ($(words $(SRC)),1)
    $(error Multiple .cpp files found: $(SRC). Please keep only one .cpp file in the root directory)
endif

# Build folder
BUILD_DIR := build
DIFFTOOL := diff -u --color=auto

# Executable name = source file name without the .cpp extension, inside build/
OUT := $(BUILD_DIR)/$(basename $(SRC))

# Detect available test cases
TEST_CASES := $(patsubst %.in,%,$(wildcard *.in))


# ========================
# Default target: compile and run with 1.in
# ========================
all: $(OUT)
	@if [ -f 1.in ]; then \
		echo "$(CYAN)===== Running with 1.in =====$(RESET)"; \
		./$(OUT) < 1.in; \
	else \
		echo "$(YELLOW)===== No 1.in found, just compiling... =====$(RESET)"; \
	fi


# ========================
# Compile targets
# ========================
compile: $(OUT)

# Rule to build the executable
$(OUT): $(SRC) | $(BUILD_DIR)
	@echo "$(BLUE)===== Compiling $(SRC).cpp =====$(RESET)"
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# Ensure build directory exists
$(BUILD_DIR):
	@echo "$(BLUE)===== Creating build directory... =====$(RESET)"
	mkdir -p $(BUILD_DIR)


# ========================
# Diff targets
# ========================
# Usage: make diff      → runs with 1.in and compares with 1.out
#        make diff2     → runs with 2.in and compares with 2.out
diff: $(OUT)
	@$(call check_test_files,1)
	@echo "$(PURPLE)===== Comparing output with 1.out =====$(RESET)"
	@if ./$(OUT) < 1.in | $(DIFFTOOL) 1.out - >/dev/null 2>&1; then \
		echo "$(GREEN)===== Test 1: PASSED =====$(RESET)"; \
	else \
		echo "$(RED)===== Test 1: FAILED =====$(RESET)"; \
		echo "$(YELLOW)===== Diff output: =====$(RESET)"; \
		./$(OUT) < 1.in | $(DIFFTOOL) 1.out -; \
	fi

diff%: $(OUT)
	@$(call check_test_files,$*)
	@echo "$(PURPLE)===== Comparing output with $*.out =====$(RESET)"
	@if ./$(OUT) < $*.in | $(DIFFTOOL) $*.out - >/dev/null 2>&1; then \
		echo "$(GREEN)===== Test $*: PASSED =====$(RESET)"; \
	else \
		echo "$(RED)===== Test $*: FAILED =====$(RESET)"; \
		echo "$(YELLOW)===== Diff output: =====$(RESET)"; \
		./$(OUT) < $*.in | $(DIFFTOOL) $*.out -; \
	fi


# ==================================
# Test targets
# ==================================
# Usage: make test     → tests all available cases automatically
# ==================================

# Test all available test cases with better formatting
test: $(OUT)
	@echo "$(CYAN)===== Testing all available cases =====$(RESET)"
	@if [ -z "$(TEST_CASES)" ]; then \
		echo "$(YELLOW)===== No test cases found =====$(RESET)"; \
		exit 0; \
	fi; \
	passed=0; total=0; failed_cases=""; \
	for case in $(TEST_CASES); do \
		total=$$((total + 1)); \
		if [ -f "$$case.out" ]; then \
			printf "$(BLUE)===== Testing $$case... =====$(RESET) "; \
			if ./$(OUT) < "$$case.in" | $(DIFFTOOL) "$$case.out" - >/dev/null 2>&1; then \
				echo "$(GREEN)✓ PASSED$(RESET)"; \
				passed=$$((passed + 1)); \
			else \
				echo "$(RED)✗ FAILED$(RESET)"; \
				echo "$(YELLOW)===== Diff output for $$case: =====$(RESET)"; \
				./$(OUT) < "$$case.in" | $(DIFFTOOL) "$$case.out" -; \
				failed_cases="$$failed_cases $$case"; \
			fi; \
		else \
			printf "$(YELLOW)===== $$case: No expected output file =====$(RESET)\n"; \
		fi; \
	done; \
	echo ""; \
	if [ $$passed -eq $$total ] && [ $$total -gt 0 ]; then \
		echo "$(GREEN)===== All tests passed! ($$passed/$$total) =====$(RESET)"; \
	elif [ $$passed -gt 0 ]; then \
		echo "$(YELLOW)===== Summary: $$passed/$$total tests passed =====$(RESET)"; \
		if [ -n "$$failed_cases" ]; then \
			echo "$(RED)===== Failed cases:$$failed_cases =====$(RESET)"; \
		fi; \
	else \
		echo "$(RED)===== All tests failed ($$passed/$$total) =====$(RESET)"; \
	fi


# ========================
# Run targets
# ========================
# Run with multiple inputs
# Usage:
#   make run                → runs with 1.in
#   make run CASES="1 2 3"  → runs with 1.in, 2.in, 3.in
CASES ?= 1
run: $(OUT)
	@for case in $(CASES); do \
		if [ -f $$case.in ]; then \
			echo "$(CYAN)===== Running $$case.in =====$(RESET)"; \
			./$(OUT) < $$case.in; \
			echo ""; \
		else \
			echo "$(RED)===== File $$case.in not found! =====$(RESET)"; \
		fi; \
	done

# Run with custom input
input: $(OUT)
	@echo "$(CYAN)===== Enter input (Ctrl+D to finish) =====$(RESET)"
	@./$(OUT)


# ========================
# Timing and benchmarking
# ========================
# Time execution with specific input
time: $(OUT)
	@$(call check_input_file,1)
	@echo "$(PURPLE)===== Timing execution with 1.in (debug) =====$(RESET)"
	@time ./$(OUT) < 1.in

time%: $(OUT)
	@$(call check_input_file,$*)
	@echo "$(PURPLE)===== Timing execution with $*.in (debug) =====$(RESET)"
	@time ./$(OUT) < $*.in


# ========================
# Debug targets
# ========================
debug: $(OUT)
	@$(call check_input_file,1)
	@if [ "$$(uname)" = "Darwin" ]; then \
		echo "$(PURPLE)===== Running with lldb =====$(RESET)"; \
		lldb -- $(OUT); \
	else \
		echo "$(PURPLE)===== Running with gdb =====$(RESET)"; \
		gdb --args $(OUT); \
	fi

valgrind: $(OUT)
	@$(call check_input_file,1)
	@if [ "$$(uname)" = "Darwin" ]; then \
		echo "$(PURPLE)===== Running with leaks (macOS) =====$(RESET)"; \
		leaks --atExit -- ./$(OUT) < 1.in; \
	else \
		echo "$(PURPLE)===== Running with valgrind =====$(RESET)"; \
		valgrind --leak-check=full --show-leak-kinds=all ./$(OUT) < 1.in; \
	fi


# ========================
# Utility targets
# ========================
# Show detailed project info
info:
	@echo "$(CYAN)===== Project Information =====$(RESET)"
	@echo "$(BLUE)Source file:$(RESET) $(SRC)"
	@echo "$(BLUE)Debug executable:$(RESET) $(OUT)"
	@echo "$(BLUE)Build directory:$(RESET) $(BUILD_DIR)"
	@echo ""
	@echo "$(CYAN)===== Available Test Cases =====$(RESET)"
	@if [ -n "$(TEST_CASES)" ]; then \
		for case in $(TEST_CASES); do \
			if [ -f "$$case.out" ]; then \
				echo "  $(GREEN)$$case$(RESET) (with expected output)"; \
			else \
				echo "  $(YELLOW)$$case$(RESET) (no expected output)"; \
			fi; \
		done; \
	else \
		echo "  $(YELLOW)No test cases found$(RESET)"; \
	fi
	@echo ""
	@echo "$(CYAN)===== Build Status =====$(RESET)"
	@if [ -f "$(OUT)" ]; then \
		echo "  $(GREEN)Debug build: exists$(RESET)"; \
	else \
		echo "  $(RED)Debug build: not found$(RESET)"; \
	fi

# Clean up executables
clean:
	@echo "$(YELLOW)===== Cleaning build directory... =====$(RESET)"
	rm -rf $(BUILD_DIR)
	@echo "$(GREEN)===== Clean complete =====$(RESET)"

# Watch for changes and auto-compile
watch:
	@echo "$(CYAN)===== Watching for changes... (Ctrl+C to stop) =====$(RESET)"
	@while true; do \
		if [ "$(SRC)" -nt "$(OUT)" ]; then \
			echo "$(YELLOW)===== File changed, recompiling... =====$(RESET)"; \
			$(MAKE) compile; \
		fi; \
		sleep 1; \
	done

# Help target with better formatting
help:
	@echo "$(CYAN)===== Available Make Targets =====$(RESET)"
	@echo ""
	@echo "$(BLUE)Build Targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)          - Compile and run with 1.in (default)"
	@echo "  $(GREEN)compile$(RESET)      - Compile debug version only"
	@echo ""
	@echo "$(BLUE)Run Targets:$(RESET)"
	@echo "  $(GREEN)run$(RESET)          - Run with test cases (CASES=\"1 2 3\")"
	@echo "  $(GREEN)input$(RESET)        - Run with manual input"
	@echo ""
	@echo "$(BLUE)Testing Targets:$(RESET)"
	@echo "  $(GREEN)diff$(RESET)         - Compare output with 1.out"
	@echo "  $(GREEN)diff2$(RESET)        - Compare output with 2.out"
	@echo "  $(GREEN)test$(RESET)         - Test all available cases automatically"
	@echo ""
	@echo "$(BLUE)Timing/Benchmark:$(RESET)"
	@echo "  $(GREEN)time$(RESET)         - Time execution with 1.in (debug)"
	@echo "  $(GREEN)time2$(RESET)        - Time execution with 2.in (debug)"
	@echo ""
	@echo "$(BLUE)Debug Targets:$(RESET)"
	@echo "  $(GREEN)debug$(RESET)        - Run with gdb debugger"
	@echo "  $(GREEN)valgrind$(RESET)     - Run with valgrind memory checker"
	@echo ""
	@echo "$(BLUE)Utility Targets:$(RESET)"
	@echo "  $(GREEN)info$(RESET)         - Show detailed project information"
	@echo "  $(GREEN)clean$(RESET)        - Remove build directory"
	@echo "  $(GREEN)watch$(RESET)        - Auto-recompile on file changes"
	@echo "  $(GREEN)help$(RESET)         - Show this help message"
	@echo ""
	@echo "$(YELLOW)Examples:$(RESET)"
	@echo "  make run CASES=\"1 2 3\"     - Run with test cases 1, 2, and 3"
	@echo "  make diff5                  - Compare output with 5.out"

# ========================
# Helper functions
# ========================
define check_input_file
	@if [ ! -f $(1).in ]; then echo "$(RED)===== File $(1).in not found! =====$(RESET)"; exit 1; fi
endef

define check_test_files
	@if [ ! -f $(1).in ]; then echo "$(RED)===== File $(1).in not found! =====$(RESET)"; exit 1; fi
	@if [ ! -f $(1).out ]; then echo "$(RED)===== File $(1).out not found! =====$(RESET)"; exit 1; fi
endef

.PHONY: all compile diff test run input time debug valgrind info clean watch help
