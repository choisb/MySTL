#include "vector.h"
#include <iostream>
#include <string>

void MyVectorTest();
void Constructor();

int main()
{
	MyVectorTest();
	return 0;
}

void MyVectorTest()
{
	Constructor();

}
void Constructor()
{
	struct Data {
		Data(int num) : index(num)
		{
			static int cnt = 0;
			//index = cnt++;
			std::cout << "Data(): " << index << std::endl;
		}
		~Data()
		{
			std::cout << "~Data(): " << index << std::endl;
		}
		int index;
	};

	//my::vector<Data> vec1;	// fine
	//my::vector<Data> vec2(5); // must error 2512

	//my::vector<Data> vec2(5, Data(10));
	//std::vector<Data> vec3(5, 11); //fine


}