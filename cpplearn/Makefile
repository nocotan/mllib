all: run

BAZEL=$(shell which bazel)

.PHONY: run
run : build
	$(BAZEL)

.PHONY: build
build :
	$(BAZEL)

.PHONY: clean
clean :
	$(BAZEL) clean
