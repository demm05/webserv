check:
	cppcheck --inconclusive --std=c++98 src/ include/

compiledb:
	@compiledb make -n all > /dev/null 2>&1

v valgrind:
	@valgrind --leak-check=full ./$(NAME) $(ARGS)
