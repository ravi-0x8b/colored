#include <iostream>
#include <fstream>

struct Color {
	char r;
	char g;
	char b;
}color, background;

void saveColoredText();
void showColoredText();

int main(int argc, char** argv) {
	//saveColoredText();
	showColoredText();
	return 0;
}

void saveColoredText() {
	char message[80];
	std::cout << "Enter a message: ";
	std::cin.getline(message, 80);

	// get text color
	std::cout << "Text color: ";
	std::cin >> color.r;
	std::cin >> color.g;
	std::cin >> color.b;

	// get text background
	std::cout << "Text color: ";
	std::cin >> background.r;
	std::cin >> background.g;
	std::cin >> background.b;

	// save all data
	std::ofstream save;
	save.open("colored.color", std::ios_base::out | std::ios_base::app | std::ios_base::binary);
	save.write((char*)&message, sizeof(message));
	save.write((char*)&color, sizeof(Color));
	save.write((char*)&background, sizeof(background));
	save.close();
}

void showColoredText() {
	char message[80];

	std::ifstream readf;
	readf.open("colored.color", std::ios_base::in | std::ios_base::binary);
	if (!readf.is_open()) {
		std::cerr << "Error: Failed to open the file.\n";
		return;
	}
	readf.read((char*)&message, sizeof(message));
	readf.read((char*)&color, sizeof(Color));
	readf.read((char*)&background, sizeof(Color));
	readf.close();

	char templat3[24] = "\033[38;5;ccc;48;5;cccm";
	templat3[7] = color.r;
	templat3[8] = color.g;
	templat3[9] = color.b;

	templat3[16] = background.r;
	templat3[17] = background.g;
	templat3[18] = background.b;

	std::cout << '\n' << templat3 << message << "\033[m\n";
}