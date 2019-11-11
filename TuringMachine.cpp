// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <thread>

struct Instruction
{
	std::string currentState;
	char currentElement;
	char newElement;
	char direction;
	std::string newState;
};

int Tiuringas(std::string failas)
{
	std::string cSt, nSt;
	char dir, cS, nS;

	bool loop_on = true;
	bool modifikacija = true;

	std::string juosta;
	std::string busena = "0";
	char kryptis;
	int galvutes_pozicija = 0;

	int loop_counter = 0;

	bool completed = false;

	int instruction_number = 0;

	struct Instruction instruction;

	std::vector<Instruction> instructionList;

	std::ifstream file;
	file.open(failas);
	if (!file.is_open())
		std::cout << "can not open the file" << std::endl;
	else
	{
		file >> galvutes_pozicija;
		file >> juosta;

		while (file >> cSt >> cS >> nS >> dir >> nSt)
		{
			instructionList.push_back(instruction);

			instructionList[instruction_number].currentState = cSt;
			instructionList[instruction_number].currentElement = cS;
			instructionList[instruction_number].newElement = nS;
			instructionList[instruction_number].direction = dir;
			instructionList[instruction_number].newState = nSt;

			instruction_number++;
		}
	}

	instruction_number = 0;

	while (true)
	{	
		if (completed) return 0;

		while (modifikacija && !completed)
		{
			if (busena == instructionList[instruction_number].currentState)
			{
				if (juosta[galvutes_pozicija] == instructionList[instruction_number].currentElement)
				{
					busena = instructionList[instruction_number].newState;

					juosta[galvutes_pozicija] = instructionList[instruction_number].newElement;

					std::cout << juosta << std::endl;

					kryptis = instructionList[instruction_number].direction;

					if (kryptis == 'R')
					{
						galvutes_pozicija++;
					}
					else if (kryptis == 'L')
					{
						galvutes_pozicija--;
					}

					if (galvutes_pozicija < 0 || galvutes_pozicija == juosta.length())//GALVUTE ISEJO UZ RIBU
					{
						completed = true;
						//return 0;
					}
					loop_counter++;
					instruction_number = 0;
				}
				else
				{
					instruction_number++;
					if (instruction_number == instructionList.size())//RADO BUSENA, BET NERADO SIMBOLIO
					{
						completed = true;
						//return 0;
					}
					loop_counter++;//PASALINUS SITA, BUS SKAICIUOJAMI TIK TIE CIKLAI, KUR JUOSTA BUVO MODIFIKUOTA
				}
			}
			else
			{
				instruction_number++;
				if (instruction_number == instructionList.size())
				{
					completed = true;
					//return 0;
				}
			}
		}
	}
	return 0;
}

int main()
{	
	int pasirinkimas;
	std::string failas[4] = { "1.txt","2.txt","3.txt","4.txt" };
	
	std::cout<<"PASIRINKITE FAILA (1, 2, 3, 4)- (0) IVIKDYS 4 PROGRAMAS"<<std::endl;
	std::cin >> pasirinkimas;

	if (pasirinkimas == 0)
	{
		std::thread t1(Tiuringas, failas[0]);
		std::thread t2(Tiuringas, failas[1]);
		std::thread t3(Tiuringas, failas[2]);
		std::thread t4(Tiuringas, failas[3]);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
	}
	else if (pasirinkimas > 0 && pasirinkimas < 5) Tiuringas(failas[pasirinkimas - 1]); // paleidzia tik viena faila

	return 0;
}

