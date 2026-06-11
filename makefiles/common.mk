# Derive VERSION_STRING from git state unless preset (e.g. by CI):
# - clean checkout exactly on a tag -> tag name without leading "v" (e.g. 2.1.2)
# - otherwise -> short commit hash, with "-dirty" suffix if the tree is dirty
ifeq ($(origin VERSION_STRING),undefined)
GIT_EXACT_TAG := $(shell git -c safe.directory='*' describe --exact-match --tags HEAD 2>/dev/null)
GIT_SHORT_HASH := $(shell git -c safe.directory='*' rev-parse --short HEAD 2>/dev/null || echo unknown)
GIT_DIRTY := $(shell test -n "$$(git -c safe.directory='*' status --porcelain 2>/dev/null)" && echo dirty)

ifneq ($(GIT_DIRTY),)
VERSION_STRING := $(GIT_SHORT_HASH)-dirty
else ifneq ($(GIT_EXACT_TAG),)
VERSION_STRING := $(patsubst v%,%,$(GIT_EXACT_TAG))
else
VERSION_STRING := $(GIT_SHORT_HASH)
endif
endif
