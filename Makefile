CXX          ?= g++
QDP_DIR      ?= $(HOME)/.usr/qdp_debug
OPENQCD_DIR  ?= openqcd
MPI_DIR      ?= /usr/lib/openmpi

CXXFLAGS     := -std=c++11 -g -Iinclude -I$(OPENQCD_DIR)/include\
								-I$(MPI_DIR)/include\
								$(shell $(QDP_DIR)/bin/qdp++-config --cxxflags)

QDP_LIBFLAGS := $(shell $(QDP_DIR)/bin/qdp++-config --libs)\
								$(shell $(QDP_DIR)/bin/qdp++-config --ldflags)

SRCDIR    := programs
LIBDIR    := library
BINDIR    := bin
OBJDIR    := $(LIBDIR)/obj
DEPDIR    := .dep
OBJDEPDIR := $(DEPDIR)/obj

SRCS     := $(wildcard $(SRCDIR)/*.cpp)
EXECS    := $(SRCS:$(SRCDIR)/%.cpp=$(BINDIR)/%)
DEPS     := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)
LIBSRCS  := $(wildcard $(LIBDIR)/*.cpp)
LIBOBJS  := $(LIBSRCS:$(LIBDIR)/%.cpp=$(OBJDIR)/%.o)
LIBDEPS  := $(LIBSRCS:$(LIBDIR)/%.cpp=$(OBJDEPDIR)/%.d)

all: $(EXECS) $(OPENQCD_DIR)
.PHONY: clean all

bin/chroma_to_openqcd : $(SRCDIR)/chroma_to_openqcd.cpp $(LIBOBJS) $(DEPDIR)/chroma_to_openqcd.d | $(BINDIR)
	@echo CXX $@
	@$(CXX) $(CXXFLAGS) $< -o $@ $(QDP_LIBFLAGS) -lboost_program_options

$(OBJDIR)/%.o : $(LIBDIR)/%.cpp $(OBJDEPDIR)/%.d | $(OBJDIR)
	@echo CXX $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(DEPDIR)/%.d: $(SRCDIR)/%.cpp | $(DEPDIR)
	@$(CXX) $(CXXFLAGS) -MM -MP -MT $(BINDIR)/$(patsubst $(SRCDIR)/%.cpp,%,$<) -MF $@ $<

$(OBJDEPDIR)/%.d: $(LIBDIR)/%.cpp | $(OBJDEPDIR)
	@$(CXX) $(CXXFLAGS) -MM -MP -MT $(OBJDIR)/$(patsubst $(LIBDIR)/%.cpp,%.o,$<) -MF $@ $<

-include $(DEPS)

clean:
	rm -rf $(BINDIR) $(DEPDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

$(DEPDIR):
	@mkdir -p $(DEPDIR)

$(OBJDEPDIR):
	@mkdir -p $(OBJDEPDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OPENQCD_DIR):
	$(error The openqcd folder does not exist, please link it in. Expected location "$(OPENQCD_DIR)")
