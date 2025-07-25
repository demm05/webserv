check:
	cppcheck --inconclusive --std=c++98 src/ include/

compiledb:
	@compiledb make -n all build_tests > /dev/null 2>&1

v valgrind:
	@valgrind --leak-check=full ./$(NAME) $(ARGS)

i init:
	@git submodule update --init --remote --recursive
