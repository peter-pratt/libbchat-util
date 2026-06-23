H_FILES = $(wildcard ../../include/bchat/config/*.h ../../include/bchat/config/*/*.h)
HPP_FILES = $(wildcard ../../include/bchat/config/*.hpp ../../include/bchat/config/*/*.hpp)

.PHONY: clean
clean:
	rm -rf ./dist

.PHONY: build-hpp
build-hpp:
	./make-docs.sh dist/libbchat-util-cpp $(HPP_FILES)

.PHONY: build-h
build-h:
	./make-docs.sh dist/libbchat-util-c $(H_FILES)

.PHONY: build-all
build-all: build-h build-hpp

.PHONY: serve-c
serve-c:
	cd dist/libbchat-util-c/site && python -m http.server 8000 && cd -

.PHONY: serve-cpp
serve-cpp:
	cd dist/libbchat-util-cpp/site && python -m http.server 8001 && cd -

# Developer commands: Build and serve a site inside of dist/ using the mkdocs development server.
# NOTE: Any changes to dist/ will be hot-reloaded but are not tracked by git.

.PHONY: dev-c
dev-c: build-h
	cd dist/libbchat-util-c && mkdocs serve && cd -

.PHONY: dev-cpp
dev-cpp: build-hpp
	cd dist/libbchat-util-cpp && mkdocs serve && cd -
