CXX=g++
CXXFLAGS=-Wall -g -O0 -std=c++14
TARGET=tmp

# ANSI color codes
GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m # No Color

all: $(TARGET)

$(TARGET): tmp.cpp
	@$(CXX) $(CXXFLAGS) -o $(TARGET) tmp.cpp

run: all
	@./$(TARGET)

test: all
	@chmod +x test_cases.sh
	@./test_cases.sh | awk '{ \
		if ($$0 ~ /^PASS:/) \
			printf "$(GREEN)%s$(NC)\n", $$0; \
		else if ($$0 ~ /^FAIL:/) \
			printf "$(RED)%s$(NC)\n", $$0; \
		else \
			print $$0; \
	}'
	@echo "$(GREEN)All tests completed.$(NC)"

clean:
	rm -f $(TARGET)
