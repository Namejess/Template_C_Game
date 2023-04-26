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
SRCS    := $(wildcard $(SRCDIR)/*.c) $(wildcard *.c)
OBJS    := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS    := $(OBJS:.o=.d)
EXEC    := Shooter

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -I$(INCDIR)

$(OBJDIR):
	mkdir -p $@

clean:
	$(RM) -r $(OBJDIR) $(EXEC)

-include $(DEPS)
