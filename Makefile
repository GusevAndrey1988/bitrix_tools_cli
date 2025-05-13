compile:
	@echo "---Build---"
	@meson compile -C ./builddir
	@echo "---Run test---"
	@./builddir/run_test