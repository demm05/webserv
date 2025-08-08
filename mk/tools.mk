check:
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem --suppress=missingInclude --std=c++98 src/ inc/

compiledb:
	@compiledb make -n $(NAME) build_tests > /dev/null 2>&1

v valgrind:
	@valgrind --leak-check=full ./$(NAME) $(ARGS)

i init:
	@git submodule update --init --remote --recursive

doc:
	@test -f Doxyfile || (doxygen -g && cat Doxyfile.template > Doxyfile)
	@doxygen Doxyfile
