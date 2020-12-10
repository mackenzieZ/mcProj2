#Make file, use 'make all'

TARGET = build/test
OBJDIR = build/obj
CXX = g++
CXX_FLAGS = -std=c++17 -g
LINK_FLAGS = -L'$(CURDIR)/OpenXLSX/build/output/' -lOpenXLSX-static -OpenXLSX-static
COMP_FLAGS = -I'$(CURDIR)/OpenXLSX/library' -I'$(CURDIR)/OpenXLSX/build/library' -I'$(CURDIR)/headers' 

all: $(TARGET)

$(TARGET): $(OBJDIR)/testMenu.o $(OBJDIR)/menu.o
	$(CXX) $(CXX_FLAGS) $(OBJDIR)/testMenu.o -o $(TARGET) $(LINK_FLAGS)

# $(OBJDIR)/ExcelReader.o: ExcelReader.cpp
# 	$(CXX) $(CXX_FLAGS) -c $< $(COMP_FLAGS) -o $@

$(OBJDIR)/menu.o: menu.cpp
	$(CXX) $(CXX_FLAGS) -c $< $(COMP_FLAGS) -o $@

$(OBJDIR)/testMenu.o: testMenu.cpp
	$(CXX) $(CXX_FLAGS) -c $< $(COMP_FLAGS) -o $@


clean:
	-rm -f $(OBJDIR)/*.o
	-rm -f $(TARGET)
