all: generator consumer dispatcher
    
generator: generator.cpp
	g++ -Wall -g -o generator generator.cpp

consumer: consumer.cpp
	g++ -Wall -g -o consumer consumer.cpp

dispatcher: dispatcher.cpp
	g++ -Wall -g -o dispatcher dispatcher.cpp

clean:
	rm -f *.o *~ generator consumer dispatcher core
