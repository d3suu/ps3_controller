#include <iostream>
#include <fstream>
#include <cstdint>

int main(){
std::ifstream eventFile("/dev/input/event14", std::ios::binary); // "pci-0000:00:14.0-usb-0:1:1.0-event" (NOT "-joystick"!)
	union boo {
		char memblock[24];
		uint16_t intblock[12];
	} s;

	struct foo {
		int X;
		int Y;
	} pad;

	while(true){
		eventFile.read(s.memblock, 24);
		if(s.intblock[18] > 0x00){
			if(s.memblock[18] == 0x01){ // front, rear; 0 = pad is vertical; front is positive
				//std::cout << (int)s.memblock[20] << "\n";
			}
			if(s.memblock[18] == 0x02){ // front, rear; 0 = pad is horizontal; front is positive
				//std::cout << (int)s.memblock[20] << "\n";
				pad.X = (int)s.memblock[20];
			}
			if(s.memblock[18] == 0x00){ // left, right; 0 = pad is on flat surface; left is positive
				if(s.memblock[20] != 0){
					//std::cout << (int)s.memblock[20] << "\n";
					pad.Y = (int)s.memblock[20];
				}
			}
		}
		std::cout << "X: " << pad.X << "\tY: " << pad.Y << "\n";
	}
	return 0;
}
