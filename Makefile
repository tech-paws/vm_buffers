BUILDDIR = build
LDFLAGS =
CXX = clang++
CXXFLAGS = -I. -Isrc/ -Ipublic/cpp/ -Wall -std=c++17 -g3

UNAME_S := $(shell uname -s)

SOURCES := $(shell find src -type f -name '*.cpp' ! -name 'tests.cpp' -maxdepth 1)
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.cpp=%.o))

LIBRARY = libvm_buffers.so

build: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CXX) -shared $(LDFLAGS) $(OBJECTS) -o build/$(LIBRARY)

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(BUILDDIR)/$(dir $<)
	$(CXX) $(CXXFLAGS) $(IMGUI_FLAGS) -c $< -o $@

test: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) src/tests.cpp -o build/test
	./build/test

clean:
	rm -rf $(BUILDDIR)
