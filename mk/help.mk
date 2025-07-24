RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
CYAN	= \033[0;36m
WHITE	= \033[0;37m
RESET	= \033[0m

HELP_STAMP	:=	.help_shown.stamp

ifeq ($(shell test -f $(HELP_STAMP) || echo 1), 1)
	.DEFAULT_GOAL	:=	first-run-help
else
	.DEFAULT_GOAL	:=	all
endif

first-run-help:
	@$(MAKE) --no-print-directory help
	@touch $(HELP_STAMP)

help:
	@echo "$(PURPLE)╔══════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(PURPLE)║                     $(CYAN)W E B S E R V   M A K E F I L E$(PURPLE)          ║$(RESET)"
	@echo "$(PURPLE)╚══════════════════════════════════════════════════════════════╝$(RESET)\n"
	@echo "$(CYAN)USAGE: make [TARGET] [OPTIONS]$(RESET)\n"
	@echo "$(YELLOW)📋 Build Targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)         Build the project (default)."
	@echo "  $(GREEN)re$(RESET)           Clean and rebuild the project."
	@echo "  $(GREEN)clean, c$(RESET)     Remove object files."
	@echo "  $(GREEN)fclean, f$(RESET)    Remove all generated files (incl. executable).\n"
	@echo "$(YELLOW)🚀 Run & Test Targets:$(RESET)"
	@echo "  $(GREEN)run, r$(RESET)       Build and run the program."
	@echo "  $(GREEN)rerun, rr$(RESET)    Rebuild and run the program."
	@echo "  $(GREEN)valgrind, v$(RESET)  Run with Valgrind memory checker.\n"
	@echo "$(YELLOW)🔧 Development Tools:$(RESET)"
	@echo "  $(GREEN)check$(RESET)        Run static analysis with cppcheck."
	@echo "  $(GREEN)compiledb$(RESET)    Generate compile_commands.json for your editor.\n"
	@echo "$(YELLOW)⚙️  Run Options:$(RESET)"
	@echo "  $(GREEN)ARGS=$(RESET)        Pass arguments to the executable."
	@echo "               e.g., make run ARGS=\"config/default.conf\""

.PHONY: help first-run-help
