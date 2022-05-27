thread: thread.cc
	g++ -std=c++20 -Wall -pthread -o thread thread.cc

UDP: sender listener
	
sender: UDP_multicast_sender.cc
	g++ -std=c++20 -Wall UDP_multicast_sender.cc -o sender

listener: UDP_multicast_listener.cc
	g++ -std=c++20 -Wall UDP_multicast_listener.cc -o listener

clean:
	rm ./thread