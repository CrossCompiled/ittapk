ALL_LECTURES = $(dir $(wildcard lecture*/) )
ALL_CLEAN_TARGETS = $(ALL_LECTURES:/=_clean)
ALL_TEST_TARGETS = $(ALL_LECTURES:/=_tests)
ALL_RUN_TARGETS = $(ALL_LECTURES:/=_run)
ALL_COVER_TARGETS = $(ALL_LECTURES:/=_cover)

.PHONY: all clean run cover

all: $(ALL_TEST_TARGETS)

run: $(ALL_RUN_TARGETS)

cover: $(ALL_COVER_TARGETS)

clean: $(ALL_CLEAN_TARGETS)



%_tests: %
	@cd $</build && \
	cmake .. && \
	cmake --build .

%_run: % %_tests
	@cd $</build && \
	find . -name "*.gcda" -type f -delete; \
	ctest -V

%_cover: % %_run
	@cd $< && \
	gcovr --exclude="build.*" --exclude="test.*" -b -r . && \
	gcovr --exclude="build.*" --exclude="test.*" -b -r . --html --html-details -o html/coverage.html

%_clean: %
	@echo "Cleaning $<"
	@cd $</build && \
	rm -r CMakeFiles


