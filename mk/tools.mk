check:
	cppcheck --inconclusive --std=c++98 src/ include/

cdb compiledb:
	@compiledb make -n $(NAME) build_tests > /dev/null 2>&1

v valgrind:
	@valgrind --leak-check=full ./$(NAME) $(ARGS)

i init:
	@git submodule update --init --remote --recursive

doxy:
	@test -f doxy/Doxyfile || (doxygen -g doxy/Doxyfile && cat doxy/Doxyfile.template > doxy/Doxyfile)
	@doxygen doxy/Doxyfile

compose:
	@docker compose up --build

.PHONY: check cdb compiledb v valgrind i init doxy compose
