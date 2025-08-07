check:
	cppcheck --inconclusive --std=c++98 src/ include/

compiledb:
	@compiledb make -n $(NAME) build_tests > /dev/null 2>&1

v valgrind:
	@valgrind --leak-check=full ./$(NAME) $(ARGS)

i init:
	@git submodule update --init --remote --recursive

doxy:
	@test -f doxy/Doxyfile || (doxygen -g && cat doxy/Doxyfile.template > doxy/Doxyfile)
	@doxygen doxy/Doxyfile
