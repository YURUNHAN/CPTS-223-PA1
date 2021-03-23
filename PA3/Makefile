OUTPUT=main
CFLAGS= -std=c++11

# %: %.c %.h
# 	gcc $(CFLAGS) -o $@ $< $(LFLAGS)

main: *.cpp
	g++ $(CFLAGS) -o $@ $<

all: $(OUTPUT)

clean:
	rm -f *.o $(OUTPUT)
