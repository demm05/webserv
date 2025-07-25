NAME		=	webserv
ARGS		?=
# =============================== COMPILATION ================================ #
CXX			=	c++
CXXFLAGS	=	-std=c++98 -Wall -Wextra -Werror -I$(HDIR)
# =============================== DIRECTORIES ================================ #
HDIR		=	inc
ODIR		=	obj
SDIR		=	src
# ================================== FILES =================================== #
SRCS		:=	$(shell find $(SDIR) -name "*.cpp")
OBJS		:=	$(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o, $(SRCS))
DIRS		=	$(sort $(dir $(OBJS)))
# ================================= INCLUDES ================================= #
include mk/tools.mk
include mk/options.mk
include mk/help.mk
include mk/tests.mk
# ================================== RULES =================================== #
all: compiledb
	@$(FMAKE) $(NAME) 

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJS): $(ODIR)/%.o: $(SDIR)/%.cpp | $(DIRS)
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(DIRS):
	@mkdir -p $@

r run:
	@$(MAKE) all > /dev/null
	@./$(NAME) $(ARGS)

rr rerun: clean r

c clean:
	@rm -rf $(ODIR)

f fclean: clean test_clean
	@rm -rf $(NAME)

re: fclean
	@$(MAKE) all

.PHONY: all build c clean f fclean re check v valgrind r run rr rerun init
