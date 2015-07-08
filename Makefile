BUILD_DIR=build
SRC_DIR=src
INCLUDE_IDR=include

CXX		 := g++ -std=c++1y
#CXX		 := clang -std=c++1y
#CXXFLAGS := -g -ggdb -Wall
CXXFLAGS :=  -O3 -Wall

SRCEXT 	:= cpp

SOURCES := $(shell find $(SRC_DIR) -type f -name *.$(SRCEXT))

OBJECTS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SRCEXT)=.o))

LIB 	:= -lprofiler -pthread
INC		:= -I include

all:	$(OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRCEXT)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD $(INC) -o $@ $< $(LIB)
	@mv -f $(BUILD_DIR)/$*.d $(BUILD_DIR)/$*.d.tmp
	@sed -e 's|.*:|$(BUILD_DIR)/$*.o:|' < $(BUILD_DIR)/$*.d.tmp > $(BUILD_DIR)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILD_DIR)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILD_DIR)/$*.d
	@rm -f $(BUILD_DIR)/$*.d.tmp

clean:
	@echo " Cleaning..."
	rm -rf $(BUILD_DIR)/*
# DO NOT DELETE
