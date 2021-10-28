# variables
obj_dir = bin
target_name = relations_eval
target_dir = target
objects = relations_evaluator.o


#rules
relations_eval : $(objects)
	g++ -o $(target_dir)/$(target_name) $(foreach object, $(objects), $(obj_dir)/$(object)) -Wall -std=c++14

relations_evaluator.o : relations_evaluator.cpp relations_evaluator.h
	g++ -c relations_evaluator.cpp -o $(foreach object,$(objects), $(obj_dir)/$(object))

run :
	./$(target_dir)/$(target_name)

clean :
	rm $(target_dir)/$(target_name) $(forach object, $(objects, $(obj_dir)/$(object)))
