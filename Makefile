CXX          ?= g++
QDP_DIR      ?= $(HOME)/.usr/qdp_debug
OPENQCD_DIR  ?= openqcd
MPI_DIR      ?= /usr/lib/openmpi

CXXFLAGS     := -std=c++11 -g -Iinclude -I$(OPENQCD_DIR)/include\
								-I$(MPI_DIR)/include\
								$(shell $(QDP_DIR)/bin/qdp++-config --cxxflags)

QDP_LIBFLAGS := $(shell $(QDP_DIR)/bin/qdp++-config --libs)\
								$(shell $(QDP_DIR)/bin/qdp++-config --ldflags)

SRCDIR := programs
BINDIR := bin
DEPDIR := .dep

SRCS     := $(wildcard $(SRCDIR)/*.cpp)
EXECS    := $(SRCS:$(SRCDIR)/%.cpp=$(BINDIR)/%)
DEPS     := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)

all: $(EXECS) $(OPENQCD_DIR)
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

$(OPENQCD_DIR):
	$(error The openqcd folder does not exist, please link it in. Expected location "$(OPENQCD_DIR)")
