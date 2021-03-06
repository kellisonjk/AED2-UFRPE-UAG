/*
* Data.h
*
*  Created on: May 11, 2015
*      Author: Kellison
*/

#ifndef DATA_H_
#define DATA_H_

#include <iostream>
#include <math.h>

#define CONST_A 0.752

using namespace std;

class Data{
	public:
		Data();
		Data(string, int);
		string getKey();
		void setKey(string);
		int getHash(int);
		int getHash(int, int);
		friend ostream& operator<< (ostream&, Data&);
		bool operator== (Data data);
		
		string getName();
		int getAge();

		virtual ~Data();
	private:
		string name;
		int age;	
};

#endif /* DATA_H_ */