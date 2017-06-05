CXX      ?= g++
CXXFLAGS := -std=c++11 -Iinclude -g -I$(HOME)/.usr/include -I/usr/include/libxml2

QDP_LIBFLAGS := $(shell $(HOME)/.usr/qdp_debug/bin/qdp++-config --libs)\
								$(shell $(HOME)/.usr/qdp_debug/bin/qdp++-config --ldflags)

SRCDIR := programs
BINDIR := bin
DEPDIR := .dep

SRCS     := $(wildcard $(SRCDIR)/*.cpp)
EXECS    := $(SRCS:$(SRCDIR)/%.cpp=$(BINDIR)/%)
DEPS     := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)

all: $(EXECS)

.PHONY: clean all

bin/chroma_to_openqcd : $(SRCDIR)/chroma_to_openqcd.cpp $(DEPDIR)/chroma_to_openqcd.d | $(BINDIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(QDP_LIBFLAGS) -lboost_program_options

$(DEPDIR)/%.d: $(SRCDIR)/%.cpp | $(DEPDIR)
	@$(CXX) $(CXXFLAGS) -MM -MP -MT $(BINDIR)/$(patsubst $(SRCDIR)/%.cpp,%,$<) -MF $@ $<

-include $(DEPS)

clean:
	rm -rf $(BINDIR) $(DEPDIR)

$(BINDIR):
	@mkdir $(BINDIR)

$(DEPDIR):
	@mkdir $(DEPDIR)
