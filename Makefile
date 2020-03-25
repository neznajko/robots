  prog = robots
   obj = $(prog).o
   gdb = -g
 flags = $(gdb)
    cc = g++

$(prog): $(obj)
	$(cc) $(gdb) -o $@ $^

 $(obj): $(prog).cxx
	$(cc) $(flags) -o $@ -c $<

 .PHONY: clean debug

  clean:
	$(RM) $(prog) $(obj)

  debug: flags += -DDEBUG
  debug: $(prog)
