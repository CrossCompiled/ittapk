ALL_LECTURES = $(dir $(wildcard lecture*/) )
ALL_CLEAN_TARGETS = $(ALL_LECTURES:/=_clean)
ALL_TEST_TARGETS = $(ALL_LECTURES:/=_tests)
ALL_RUN_TARGETS = $(ALL_LECTURES:/=_run)
ALL_COVER_TARGETS = $(ALL_LECTURES:/=_cover)
ALL_COVER_HTML_TARGETS = $(ALL_LECTURES:/=_cover_html)

.PHONY: all clean run cover

all: $(ALL_TEST_TARGETS)

run: $(ALL_RUN_TARGETS)

cover: $(ALL_COVER_TARGETS)

cover_html: $(ALL_COVER_HTML_TARGETS)

clean: $(ALL_CLEAN_TARGETS)



%_tests: %
	@cd $</build && \
	cmake .. && \
	cmake --build .

ifeq ($(OS),Windows_NT)
%_run: % %_tests
	@cd $</build && \
	ctest -V
else
%_run: % %_tests
	@cd $</build && \
	find . -name "*.gcda" -type f -delete; \
	ctest -V
endif

%_cover: % %_run
	@cd $< && \
	gcovr --exclude="build.*" --exclude="test.*" -b -r .

%_cover_html: % %_run
	@cd $< && \
	gcovr --exclude="build.*" --exclude="test.*" -b -r . --html --html-details -o html/coverage.html && \
	xdg-open html/coverage.html

ifeq ($(OS),Windows_NT)
%_clean: %
	@echo "Cleaning $<"
	@cd $</build && \
	rmdir /S /Q CMakeFiles
else
%_clean: %
	@echo "Cleaning $<"
	@cd $</build && \
	rm -r CMakeFiles
endif


