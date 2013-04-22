SM_SOURCES=     src/Watch.sm
SOURCES=        $(SM_SOURCES:.sm=_sm.cpp) \
                src/Watch.cpp \
                src/Input.cpp \
                src/Time.cpp \
                src/Sched.cpp \
                src/main.cpp
HEADERS=        $(SM_SOURCES:.sm=_sm.h) \
                src/Watch.h \
                src/Time.h \
                src/Sched.h \
                src/Input.h
OBJECTS=        $(SOURCES:.cpp=.o)
TARGET=         casio-fsm

# Uncomment to turn off IOStreams for debug.
# NO_STREAMS=     -nostreams

# Uncomment to turn on debug message generation.
TRACE=          -g $(NO_STREAMS)

# Uncomment to turn on serialization.
# SERIAL=         -serial

# Uncomment to turn off try/catch/rethrow generation.
# NO_CATCH=       -nocatch

# Uncomment to turn off exception throws.
# NO_EXCEPT=      -noex

SMC_ROOT=       foreign/smc_6_1_0
SMC=            java -jar $(SMC_ROOT)/bin/Smc.jar
SMC_FLAGS=      -c++ $(TRACE) $(SERIAL) $(NO_CATCH) $(NO_EXCEPT)

CXX=            c++
INCLUDE_DIRS=   -Isrc -I$(SMC_ROOT)/lib/C++
LIBS=           -lboost_chrono -lboost_program_options -lboost_system -lcurses
CPPFLAGS=       -g -Wall -Wextra $(INCLUDE_DIRS)

RM_F=           rm -f

#################################################################
# Rules.
#

%_sm.h %_sm.cpp : %.sm
		$(SMC) $(SMC_FLAGS) $<

%_sm.dot :      %.sm
		$(SMC) -graph -glevel 1 $<

%_sm.png :      %_sm.dot
		dot -T png -o $@ $<

%_sm.html :     %.sm
		$(SMC) -table $<

all :           $(TARGET)

$(TARGET) :     $(HEADERS) $(SOURCES)
		$(CXX) $(CPPFLAGS) -o $@ $(SOURCES) $(LIB_DIRS) $(LIBS)

test :          $(TARGET)

graph :         $(SM_SOURCES:%.sm=%_sm.dot)

png :           $(SM_SOURCES:%.sm=%_sm.png)

table :         $(SM_SOURCES:%.sm=%_sm.html)

clean :
		-$(RM_F) $(TARGET)
		-$(RM_F) $(OBJECTS)
		-$(RM_F) *_sm.h
		-$(RM_F) *_sm.cpp
		-$(RM_F) *_sm.dot
		-$(RM_F) *_sm.png
		-$(RM_F) *_sm.html

