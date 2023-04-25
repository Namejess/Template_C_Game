# Compiler
CC      := gcc
CFLAGS  := -Wall -Wextra -Wpedantic -std=c99 -g

# Linker
LDFLAGS := -lSDL2 -lSDL2_image

# Directories
SRCDIR  := src
INCDIR  := include
OBJDIR  := obj

# Files
SRCS    := $(wildcard $(SRCDIR)/*.c)
OBJS    := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DEPS    := $(OBJS:.o=.d)
EXEC    := Shooter

# Targets
all: $(EXEC)

$(EXEC): main.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -I$(INCDIR)

$(OBJDIR):
	mkdir -p $@

clean:
	$(RM) -r $(OBJDIR) $(EXEC)

-include $(DEPS)
