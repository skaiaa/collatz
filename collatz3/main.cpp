#include "forest.h"

using std::cin;
using std::cout;

unsigned int collatz(unsigned int number) {
		if (number % 2 == 0) return number / 2;
		else {
			if (long long unsigned int(number) * 3 + 1 > UINT_MAX) return 0;
			else return number * 3 + 1;
		}
}
void write(Table sequence, std::size_t size) {
	for (std::size_t i = 0; i < size; i++) {
		if (sequence[i] == 0) cout << "m";
		else cout << sequence[i];
		if (i != size - 1)cout << " ";
	}
}
int main() {
	int size = 0, number_of_commands = 0, number_of_executions;
	char type_of_execution;
	scanf_s("%i",&size);
	Table sequence = Table(size);
	TreeAVL sorted_sequence;
	unsigned int number;
	for (std::size_t i = 0; i < size; i++) {
		scanf_s("%u", &number);
		sequence[i] = number;

		if (number != 1) sorted_sequence.add(sequence[i], i);

	}
	scanf_s("%i",&number_of_commands);
	for (std::size_t i = 0; i < number_of_commands; i++) {
		scanf_s("%i %c",&number_of_executions, &type_of_execution);
		//scanf_s("%c", &type_of_execution);
		unsigned int index = 0;//musze tu bo sie pulta, ze nie zainicjalizowane
		for (std::size_t j = 0; j < number_of_executions; j++) {
			switch (type_of_execution) {
			case 's':
				//write(sequence, size);
				if (sorted_sequence.root != NULL) {
					index = sorted_sequence.find_min();
					sequence[index] = collatz(sequence[index]);//tutaj zwracaja indeksy do tablicy i zmieniam w tablicy, po czym dodaje
					if (sequence[index] > 1)sorted_sequence.add(sequence[index], index);
				}
				
				break;
			case 'l':
				if (sorted_sequence.root != NULL) {
					index = sorted_sequence.find_max();
					sequence[index] = collatz(sequence[index]);//tutaj zwracaja indeksy do tablicy i zmieniam w tablicy, po czym dodaje
					if (sequence[index] > 1)sorted_sequence.add(sequence[index], index);
				}
				break;
			default:
				break;
			}
		}
	}
	for (std::size_t i = 0; i < size; i++) {
		if (sequence[i] == 0) printf_s("m");
		else printf_s("%d", sequence[i]);
		if (i != size - 1) printf_s(" ");
	}
	return 0;
}