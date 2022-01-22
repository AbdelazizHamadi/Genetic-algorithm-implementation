#include <iostream>
#include <cstdlib>  
#include <vector>
#include <algorithm>
#include <ctime>
#include <Windows.h>
#include <cmath>


using namespace std;

struct bits {

	int b[16];
};

struct infos {

	string name;
	bits b;
	long integer;
	long long FunResult;
	double Prob;
};

bool compareByProb(infos  a, infos b)
{
	return a.Prob > b.Prob;
}

void Dec2Bin(int* a, int decimal) {

	int i;

	for (i = 0; decimal > 0; i++)
	{

		a[i] = decimal % 2;
		decimal = decimal / 2;

	}

}

int Bin2Dec(int* a)
{

	int decimal = 0;
	int base = 1;

	for (int i = 0; i <= 15; i++) {
		if (a[i] == 1)
			decimal += base;

		base = base * 2;
	}

	return decimal;
}


// fonction objectif 
long long fun(int number) {

	return pow(number,2);
	//return (0.25 *  abs(15 * number * number - number * number * number) + 4);
}

//this function is to generate a unique Random number from 0 to ‭65 535‬ 
int GenerateRandom(long long * a, long  Maxrange) {

	srand((unsigned)time(0));
	long Random = rand() % Maxrange;
	bool found = true;
	while (found) {


		for (long i = 0; i < Maxrange; i++) {

			if (Random == a[i]) {
				found = true;
				Random = rand() % Maxrange;
				break;
			}
			else {
				found = false;
			}

		}

	}

	for (long i = 0; i < Maxrange; i++) {

		if (a[i] == -1) {
			a[i] = Random;
			break;
		}

	}

	return Random;
}

int GenerateRandomPicking(int* a, vector<infos> Xs, float ProbAim) {

	Sleep(100);
	int Random = rand() % 6; // 3
	bool found = true;

	while (found) {

		//std :: cout << "generating rand number to pick " << Random << endl;

		for (int i = 0; i < 6; i++) {

			if (Random == a[i]) {
				//std::cout << "found on memory (one of the couples ) : " << Random << endl;
				found = true;
				Sleep(100);
				srand((unsigned)time(0));
				Random = rand() % 6;
				break;

			}

			if (Xs[Random].Prob < ProbAim) {

				//std::cout << "weak single : " << Random << " Prob : " << Xs[Random].Prob << endl;
				found = true;

				Random = rand() % 6;
				break;
			}
			else {

				found = false;
			}



		}

	}

	for (int i = 0; i < 6; i++) {

		if (a[i] == -1) {
			a[i] = Random;
			break;
		}

	}

	return Random;
}

int HowmanyCouples(vector<infos> Xs, float ProbAim) {

	int count = 0;
	int couples = 0;
	// n = n * (n-1);
	for (auto X : Xs) {

		if (X.Prob > ProbAim)
			count++;
	}

	couples = count * (count - 1);
	return count;

}

void cross(int* a, int* b, int numberofBits,float chanceOfCross) {

	Sleep(1000);
	srand((unsigned)time(0));
	int chance = rand() % 100;



	if (chance < chanceOfCross) {

		std::cout << "cross happening this time : " << chance << "%" << endl;

		srand((unsigned)time(0));
		int position = rand() % numberofBits;
		std::cout << "position " << position << endl;
		int Howmany = 0;

		int diff = 15 - position;
		Howmany = rand() % (diff + 1);


		std::cout << "how many " << Howmany << endl;

		for (int i = position; i <= (position + Howmany); i++) {


			if (a[i] == 1)
				a[i] = 0;
			else
				if (a[i] == 0)
					a[i] = 1;


			if (b[i] == 1)
				b[i] = 0;
			else
				if (b[i] == 0)
					b[i] = 1;

		}


	}
	else {

		std::cout << "no chance for cross this time " << endl;
	}

}

void mutation(int* a, int* b, int numberofBits, float chanceOfNutation) {

	Sleep(1000);
	srand((unsigned)time(0));
	int chance = rand() % 100;
	

	if (chance <= chanceOfNutation) {

		std::cout << "Mutaion happening this time : " << chance << "%"<< endl;
		srand((unsigned)time(0));
		int position = rand() % numberofBits;
		std::cout << "position " << position << endl;

		if (a[position] == 1)
			a[position] = 0;
		else
			if (a[position] == 0)
				a[position] = 1;


		if (b[position] == 1)
			b[position] = 0;
		else
			if (b[position] == 0)
				b[position] = 1;

	}
	else {

		std::cout << "no chance for mutation this time " << endl;
	}


}


int main()
{
	//entier decoder 

	long long memoryofRands[65535];
	for (long i = 0; i < 65535; i++)
		memoryofRands[i] = -1;

	int memoryofRandsPick[6];
	for (int i = 0; i < 6; i++)
		memoryofRandsPick[i] = -1;


	bits Initial = { 0 };

	//first generation 
	infos x1 = { "x1",Initial,GenerateRandom(memoryofRands,65535),fun(x1.integer),0 };
	infos x2 = { "x2",Initial,GenerateRandom(memoryofRands,65535),fun(x2.integer),0 };
	infos x3 = { "x3",Initial,GenerateRandom(memoryofRands,65535),fun(x3.integer),0 };
	infos x4 = { "x4",Initial,GenerateRandom(memoryofRands,65535),fun(x4.integer),0 };
	infos x5 = { "x5",Initial,GenerateRandom(memoryofRands,65535),fun(x5.integer),0 };
	infos x6 = { "x6",Initial,GenerateRandom(memoryofRands,65535),fun(x6.integer),0 };



	vector <infos> Xs = { x1,x2,x3,x4,x5,x6 };

	// finding bits of every X element 

	for (int i = 0; i < Xs.size(); i++) {
		Dec2Bin(Xs[i].b.b, Xs[i].integer);
	}

	// Culculating Sum to caclulate Selection Probabilte 
	double Sum = 0;

	for (auto X : Xs) {

		Sum += X.FunResult;
	}


	// caclculating Function results 
	for (int i = 0; i < Xs.size(); i++) {

	
		//double  === Llong long ?
		Xs[i].Prob = Xs[i].FunResult / Sum * 100;
		
	}



	bool running = true;
	int iteration = 0;

	std::cout << endl << "la fonction Objectif : pow(x,2) " << endl << endl;

	// showing infos of the Very First  generations 
	std::cout << "the current  generation : " << endl;

	std::cout << "\nname | integer | Function(Integer) | Propability of selection (%)" << endl;

	for (auto X : Xs) {


		std::cout << X.name << "\t" << X.integer << "\t  " << X.FunResult << "\t\t     " << X.Prob << "%" << "\t" << "Binary of (" << X.integer << ") : " << "\t";


		for (int j = 15; j >= 0; j--) {
			std::cout << X.b.b[j] << "";
		}

		std::cout << endl;
	}

	// this function sorts the vector by their Probability 
	sort(Xs.begin(), Xs.end(), compareByProb);


	float ProbAim = -1.0f;

	while (ProbAim < 0 || ProbAim > 20) {

		cout << "\n\tEnter a Probablity percentage to be eliminated (from 0% ---> 20%) : ";
		cin >> ProbAim;
	}

	float ChanceofMutation = -1.0f;

	while (ChanceofMutation < 0 || ChanceofMutation > 5) {

		cout << "\n\tEnter the chance of mutation (from 0% ---> 5%) : ";
		cin >> ChanceofMutation;
	}

	float ChanceofCross = -1.0f;

	while (ChanceofCross < 0 || ChanceofCross > 100) {

		cout << "\n\tEnter the chance of Cross (from 0% ---> 100%) : ";
		cin >> ChanceofCross;
	}


	int iterations = 0;
	 
	while (iterations < 10 || iterations > 20) {

		cout << "\n\tEnter number of iteration (from 10 ---> 20)  : ";
		cin >> iterations;
	}


	while (running && iteration < iterations) {

		std::cout << "\n ________________________ITERATION ________ " << iteration + 1 << " ______ : " << endl;

		//intialize choosing couples array  for every generation 
		for (int i = 0; i < 6; i++)
			memoryofRandsPick[i] = -1;

		// initialize sum value for every generation 
		Sum = 0;

		

		//if the best prob is superior than 80% stop the loop which already sorted "Xs[0]" always has the best Prob

		if (Xs[0].Prob >= 80) {

			running = false;
			std::cout << "\n_______________ Prob wanted been reached _______________ with : " << Xs[0].Prob << "%" << endl;


			std::cout << endl << Xs[0].name << "\t" << Xs[0].integer << "\t" << Xs[0].FunResult << "\t" << Xs[0].Prob << "%" << "\t" << "Binary of (" << Xs[0].integer << ") : " << "\t";


			for (int j = 4; j >= 0; j--) {
				std::cout << Xs[0].b.b[j] << "";
			}

			std::cout << endl;
			break;

			//break;
		}





		// generate Random couple 

		Sleep(5);

		//this is for generating unique couples 
		bool checkCouples = true;

		//this for seeing how many couples we can make with Propabilty greater than 20 



		int couplesPossible = HowmanyCouples(Xs, ProbAim);

		int ran1 = 0;
		int ran2 = 0;
		int ran3 = 0;
		int ran4 = 0;
		int ran5 = 0;
		int ran6 = 0;
		int ran7 = 0;
		int ran8 = 0;
		int ran9 = 0;
		int ran10 = 0;
		int ran11 = 0;
		int ran12 = 0;


		if (couplesPossible >= 3) {

			// couple 1 
			for (int i = 0; i < 6; i++)
				memoryofRandsPick[i] = -1;

			ran1 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);
			ran2 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);

			// std::cout << "generating first unique couple " << ran1 << " " << ran2 << endl;

			//couple 2
			for (int i = 0; i < 6; i++)
				memoryofRandsPick[i] = -1;

			ran3 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);
			ran4 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);

			while (checkCouples) {

				//std::cout << "generating second unique couple " << ran3 << " " << ran4 << endl;
				if (ran3 == ran1 && ran4 == ran2)
				{
					//std::cout << "used couple " << ran3 << " " << ran4 << endl;
					for (int i = 0; i < 6; i++)
						memoryofRandsPick[i] = -1;

					ran3 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);
					ran4 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);
				}
				else {

					checkCouples = false;
				}

			}

			checkCouples = true;

			//couple 3
			for (int i = 0; i < 6; i++)
				memoryofRandsPick[i] = -1;

			ran5 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);
			ran6 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);

			while (checkCouples) {

				//std::cout << "generating third unique couple " << ran5 << " " << ran6 << endl;
				if (ran5 == ran1 && ran6 == ran2 || ran5 == ran3 && ran6 == ran4)
				{
					//	std::cout << "used couple " << ran3 << " " << ran4 << endl;
					for (int i = 0; i < 6; i++)
						memoryofRandsPick[i] = -1;

					ran5 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);
					ran6 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);
				}
				else {

					checkCouples = false;
				}

			}


			std::cout << "\nRand picked : " << endl << endl << "couple 1 : " << Xs[ran1].name << " " << Xs[ran2].name << endl << "couple 2 : " << Xs[ran3].name << " " << Xs[ran4].name << endl << "couple 3 : " << Xs[ran5].name << " " << Xs[ran6].name << endl;

			//cross 
			Sleep(5);
			std::cout << "\nCouple 1 Cross (backwards indexing ) : " << endl;
			cross(Xs[ran1].b.b, Xs[ran2].b.b, 16,ChanceofCross);
			mutation(Xs[ran1].b.b, Xs[ran2].b.b, 16,ChanceofMutation);

			Xs[ran1].integer = Bin2Dec(Xs[ran1].b.b);
			Xs[ran2].integer = Bin2Dec(Xs[ran2].b.b);
			Xs[ran1].FunResult = fun(Xs[ran1].integer);
			Xs[ran2].FunResult = fun(Xs[ran2].integer);

			Sleep(5);
			std::cout << "\nCouple 2 Cross (backwards indexing ) : " << endl;
			cross(Xs[ran3].b.b, Xs[ran4].b.b, 16, ChanceofCross);
			mutation(Xs[ran3].b.b, Xs[ran4].b.b, 16, ChanceofMutation);

			Xs[ran3].integer = Bin2Dec(Xs[ran3].b.b);
			Xs[ran4].integer = Bin2Dec(Xs[ran4].b.b);
			Xs[ran3].FunResult = fun(Xs[ran3].integer);
			Xs[ran4].FunResult = fun(Xs[ran4].integer);

			Sleep(5);
			std::cout << "\nCouple 3 Cross (backwards indexing ) : " << endl;
			cross(Xs[ran5].b.b, Xs[ran6].b.b, 16, ChanceofCross);
			mutation(Xs[ran5].b.b, Xs[ran6].b.b,16, ChanceofMutation);

			Xs[ran5].integer = Bin2Dec(Xs[ran5].b.b);
			Xs[ran6].integer = Bin2Dec(Xs[ran6].b.b);
			Xs[ran5].FunResult = fun(Xs[ran5].integer);
			Xs[ran6].FunResult = fun(Xs[ran6].integer);

			//rearrange 
			
			
			

			
			
			

			std::cout << endl;

		}
		else {

			if (couplesPossible == 2) {


				// couple 1 
				for (int i = 0; i < 6; i++)
					memoryofRandsPick[i] = -1;

				int ran1 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);
				int ran2 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);

				//std::cout << "generating first unique couple " << ran1 << " " << ran2 << endl;

				//couple 2
				for (int i = 0; i < 6; i++)
					memoryofRandsPick[i] = -1;


				int ran3 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);
				int ran4 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);

				while (checkCouples) {

					//std::cout << "generating second unique couple " << ran3 << " " << ran4 << endl;
					if (ran3 == ran1 && ran4 == ran2)
					{
						//std::cout << "used couple " << ran3 << " " << ran4 << endl;
						for (int i = 0; i < 6; i++)
							memoryofRandsPick[i] = -1;


						ran3 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);
						ran4 = GenerateRandomPicking(memoryofRandsPick, Xs, ProbAim);
					}
					else {

						checkCouples = false;
					}

				}

				std::cout << "\nmax combination couples are 2 with superior than " << ProbAim << "%" << endl;
				std::cout << "\nRand picked : " << endl << endl << "couple 1 : " << Xs[ran1].name << " " << Xs[ran2].name << endl << "couple 2 : " << Xs[ran3].name << " " << Xs[ran4].name << endl << endl;

				//cross,mutation for couple 1
				Sleep(5);
				std::cout << "\nCouple 1 Cross (backwards indexing ) : " << endl;
				cross(Xs[ran1].b.b, Xs[ran2].b.b, 16, ChanceofCross);
				mutation(Xs[ran1].b.b, Xs[ran2].b.b,16,ChanceofMutation);

				Xs[ran1].integer = Bin2Dec(Xs[ran1].b.b);
				Xs[ran2].integer = Bin2Dec(Xs[ran2].b.b);
				Xs[ran1].FunResult = fun(Xs[ran1].integer);
				Xs[ran2].FunResult = fun(Xs[ran2].integer);

				//cross,mutation for couple 2
				Sleep(5);
				std::cout << "\nCouple 2 Cross (backwards indexing ) : " << endl;
				cross(Xs[ran3].b.b, Xs[ran4].b.b, 16, ChanceofCross);
				mutation(Xs[ran3].b.b, Xs[ran4].b.b, 16, ChanceofMutation);


				Xs[ran3].integer = Bin2Dec(Xs[ran3].b.b);
				Xs[ran4].integer = Bin2Dec(Xs[ran4].b.b);
				Xs[ran3].FunResult = fun(Xs[ran3].integer);
				Xs[ran4].FunResult = fun(Xs[ran4].integer);

				

				std::cout << endl;


			}
			else {

				std::cout << "\n no more couples possible with Probabilty superior than " << ProbAim << "%" << endl;
				std::cout << "\n Best Result :  " << endl;
				std::cout << endl << " " << Xs[0].name << "\t" << Xs[0].integer << "\t" << Xs[0].FunResult << "\t" << Xs[0].Prob << "%" << "\t" << "Binary of (" << Xs[0].integer << ") : " << "\t";

				for (int j = 15; j >= 0; j--) {
					std::cout << Xs[0].b.b[j] << "";
				}

				std::cout << endl;
				break;

			}
		}


		Sum = 0;


		// caclulating the new sum 
		for (auto X : Xs) {

			Sum += X.FunResult;
		}

		// caclculating the new probability 
		for (int i = 0; i < Xs.size(); i++) {

			Xs[i].Prob = Xs[i].FunResult / Sum * 100;
		}

		std::cout << endl;

		// this function sorts the vector by their Probability 
		sort(Xs.begin(), Xs.end(), compareByProb);

		// showing infos of the generations 
		std::cout << "the current  generation : " << endl;

		std::cout << "\nname | integer | Function(Integer) | Propability of selection (%)" << endl;

		for (auto X : Xs) {


			std::cout << X.name << "\t" << X.integer << "\t  " << X.FunResult << "\t\t     " << X.Prob << "%" << "\t" << "Binary of (" << X.integer << ") : " << "\t";


			for (int j = 15; j >= 0; j--) {
				std::cout << X.b.b[j] << "";
			}

			std::cout << endl;
		}


		iteration++;
	}

	if (iteration == iterations) {

		std::cout << "\n Best Result :  " << endl;
		std::cout << endl << " " << Xs[0].name << "\t" << Xs[0].integer << "\t" << Xs[0].FunResult << "\t" << Xs[0].Prob << "%" << "\t" << "Binary of (" << Xs[0].integer << ") : " << "\t";
	}

}