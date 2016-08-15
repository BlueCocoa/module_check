CXX = g++

PREFIX ?= /usr/local
HEADER = module_check.h
DEMO = module_check

demo : $(TARGET)
	$(CXX) -std=c++14 -fPIC demo.cpp -o $(DEMO)
    
install :
	install -m 644 $(HEADER) $(PREFIX)/include

uninstall :
	rm -f $(PREFIX)/include/$(HEADER)

clean :
	-rm -f $(DEMO)
