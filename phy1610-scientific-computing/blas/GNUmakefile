#PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../make.vars
include ../make.vars.blas

#THISDIR := phy1610-scientific-computing/blas

ifdef USE_OPENBLAS
   # ubuntu libopenblas
   CXXFLAGS += -I/usr/include/openblas
   LDFLAGS += -L/usr/lib/openblas
   LDFLAGS += -lopenblas
else
   # ubuntu libblas
   LDFLAGS += -lblas
endif

TARGETS += dscalC
DSCALC_SOURCES += dscalC.cc
DSCALC_OBJECTS := $(subst .cc,.o,$(DSCALC_SOURCES))

#TARGETS += dscalF
DSCALF_SOURCES += dscalF.cc
DSCALF_OBJECTS := $(subst .cc,.o,$(DSCALF_SOURCES))

TARGETS += ddot
DDOT_SOURCES += ddot.cc
DDOT_OBJECTS := $(subst .cc,.o,$(DDOT_SOURCES))

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

ddot : $(DDOT_OBJECTS)
	$(CXX) -o $@ $(DDOT_OBJECTS) $(LDFLAGS) $(DDOT_LDFLAGS) $(LDLIBS) $(DDOT_LDLIBS)

dscalC : $(DSCALC_OBJECTS)
	$(CXX) -o $@ $(DSCALC_OBJECTS) $(LDFLAGS) $(DSCALC_LDFLAGS) $(LDLIBS) $(DSCALC_LDLIBS)

dscalF : $(DSCALF_OBJECTS)
	$(CXX) -o $@ $(DSCALF_OBJECTS) $(LDFLAGS) $(DSCALF_LDFLAGS) $(LDLIBS) $(DSCALF_LDLIBS)

include ../make.rules
