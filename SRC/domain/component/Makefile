include ../../../Makefile.def

OBJS       = DomainComponent.o \
	Parameter.o \
	RVParameter.o \
	DVParameter.o \
	NodeResponseParameter.o \
	TclParameterCommands.o \
	MaterialStageParameter.o \
	MatParameter.o \
	TclUpdateMaterialCommand.o

# Compilation control
all:         $(OBJS)

# Miscellaneous
tidy:	
	@$(RM) $(RMFLAGS) Makefile.bak *~ #*# core

clean: tidy
	@$(RM) $(RMFLAGS) $(OBJS) *.o

spotless: clean

wipe: spotless


# DO NOT DELETE THIS LINE -- make depend depends on it.
