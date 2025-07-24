NAME		=	webserv
ARGS		=
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
# ================================== RULES =================================== #
all: $(DIRS) $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJS): $(ODIR)/%.o: $(SDIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(DIRS):
	@mkdir -p $@

r run: all
	@./$(NAME) $(ARGS)

rr rerun: clean r

c clean:
	@rm -rf $(ODIR)

f fclean: clean
	@rm -rf $(NAME)

re: fclean all
