OBJECTS=tree.o \
        hybrid.o \
        mphr.o \
        rtree.o \
        rtree_ls.o \
				bvh.o

INC=-I. -I../.

all: $(OBJECTS)

%.o: %.cpp %.h
	$(NVCC) -x cu $(NVCCFLAGS) $(INC) -dc $< -o $@ 

tree.o : ./../common/macro.h ./../common/config.h ./../common/logger.h ./rtree.h
hybrid.o : ./../common/macro.h ./../common/config.h ./../common/logger.h ./rtree.h
mphr.o : ./../common/macro.h ./../common/config.h ./../common/logger.h
bvh.o : ./../common/macro.h ./../common/config.h ./../common/logger.h
rtree.o : ./../common/macro.h ./../common/config.h ./../common/logger.h
rtree_ls.o : ./../common/macro.h ./../common/config.h ./../common/logger.h ./rtree.h

clean:
	rm -f *.o
