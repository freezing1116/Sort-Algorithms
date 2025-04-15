CXX = clang++
CXXFLAGS = -O2 -std=c++17 -g

TARGETS = tester test_logger stability_tester

all: $(TARGETS)

%: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
