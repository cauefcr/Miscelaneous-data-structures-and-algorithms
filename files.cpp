#include <iostream>
#include <fstream>

using namespace std;

int main(){
	//dat file io, son

	ifstream totally_a_file("file.txt");

	string buffer;

	getline(totally_a_file,buffer);

	cout << buffer;

	ofstream writting("out.txt");

	writting << buffer; //also works

	totally_a_file.close();
	writting.close();

	return 0;
}