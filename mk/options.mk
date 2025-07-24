MAKE	=	@make --no-print-directory

# For parallel compilation
# $(info $(MAKEFLAGS))
JOBS := $(filter -j%,$(MAKEFLAGS))
# $(info $(JOBS))

ifeq ($(JOBS),)
    ifeq ($(shell uname -s), Darwin)
        JOBS = -j$(shell sysctl -n hw.ncpu)
    else
        JOBS = -j$(shell nproc)
    endif
endif

FMAKE	=	$(MAKE) $(JOBS)

# MAKEFLAGS += $(JOBS)
# $(info $(JOBS))
