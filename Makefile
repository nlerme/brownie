# Variables
include Makefile.common
CXX       = g++
CXXFLAGS  = -O3 -Wall -g
LDFLAGS   = -L/usr/lib
INC_DIR   = -Iinclude -I/usr/include/freetype2
LIBS      = -lm -lSDL -lGL -lGLEW -lfreetype -lGLU
DOC_DIR   = doc
SRC_DIR   = src
OBJ_DIR   = obj
FILES_EXT = cpp
TARGET    = main
SRC       = $(notdir $(wildcard $(SRC_DIR)/*.$(FILES_EXT)))
OBJ       = $(SRC:%.$(FILES_EXT)=$(OBJ_DIR)/%.o)

# Rules
all: header depend $(OBJ) $(TARGET) footer

header:
	@echo -e "+-------------------------------------------------------------------------------------------------"
	@echo -e "| $(PROJECT_NAME) - $(PROJECT_DESCRIPTION)"
	@echo -e "| Version: v$(PROJECT_VERSION)"
	@echo -e "| Authors: $(PROJECT_AUTHORS)"
	@echo -e "+-------------------------------------------------------------------------------------------------\n"

depend:
	@echo -n "+ Generate dependencies : "
ifneq ($(strip $(SRC)),)
	@$(CXX) $(INC_DIR) -MM $(SRC:%=$(SRC_DIR)/%) \
	| sed -e 's:^[^ ]:$(OBJ_DIR)/&:' > Makefile.depend
endif
	@echo "OK"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(FILES_EXT)
	@echo -n "+ Compiling $(notdir $@) : "
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INC_DIR) -c $< -o $@
	@echo "OK"

$(TARGET): $(OBJ)
	@echo -n "+ Building $@ : "
	@$(CXX) $(CXXFLAGS) $(INC_DIR) $^ -o $@ $(LDFLAGS) $(LIBS)
	@echo "OK"

clean: clean_doc
	@echo -n "+ Deleting objects : "
	@rm -f $(OBJ_DIR)/*.o $(TARGET)
	@echo "OK"

doc:
	@$(MAKE) -C $(DOC_DIR) -s

clean_doc:
	@$(MAKE) -C $(DOC_DIR) -s clean

footer:
	@echo -e "\n--------------------------------------------------------------------------------------------------"

include Makefile.depend

.PHONY: doc clean clean_doc
