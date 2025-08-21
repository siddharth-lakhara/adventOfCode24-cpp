DAY ?= 1
SRC = day$(DAY).cpp
HDR = day$(DAY).h
OUT = day$(DAY)

BIN = bin

.PHONY: day utils

utils: utils.cpp
	@echo "Compiling utils..."
	@g++ utils.cpp -o $(BIN)/utils

# make day DAY=9
day: utils
	@echo "Compiling Day $(DAY)..."
	@g++ $(DAY)/$(SRC) -o $(BIN)/$(OUT)

# delete all files in BIN directory
clean:
	rm -r $(BIN)
	mkdir $(BIN)