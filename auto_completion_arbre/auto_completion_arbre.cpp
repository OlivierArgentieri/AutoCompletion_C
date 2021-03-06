// auto_completion_arbre.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Letter.h"
#include <vector>
#include <conio.h>

void fill_linked_letter_with_file(std::string file_name, Letter **letter);

// search letter and add if not exist 
void add_letter_if_not_exist(Letter **letter, char c);
// move letter
void move_to_right(Letter** current_letter);
void move_to_under(Letter** current_letter);

// print words by letter 
void print_tree(Letter * l, char * tab, int index = 0);

void init_tab(char * tab, int size);
void print_word_tab(char * tab, int size_word);
void print_first_word(Letter *l);


void find_by_letter(char * word, Letter * first_letter, int size_word, int index = -1);
int main()
{
	Letter* start;
	fill_linked_letter_with_file("liste_francais.txt", &start);

	/*
	Letter *tmp = start;
	while (tmp != nullptr)
	{
		auto t = (char *)malloc(sizeof(char) * 100);
		init_tab(t, 100);

		printf("%c", tmp->m_value);
		print_tree(tmp, t);
		tmp = tmp->m_next;
	}*/

	int index = 0;

	char test[30];
	init_tab(test, 30);
	char c;
	while ((c = _getch()) != '\n' && c != EOF)
	{
		if (c != '\0')
		{
			test[index] = c;


			print_word_tab(test, 30);
			printf("\n");

			find_by_letter(test, start, 30);
			printf("\n");
			index += 1;
			fseek(stdin, 0, SEEK_END); // clear input buffer
		}
		fseek(stdin, 0, SEEK_END); // clear input buffer
	}

	system("cls");

}

void fill_linked_letter_with_file(std::string file_name, Letter **letter)
{
	int c;
	FILE* file;
	(*letter) = (Letter *)malloc(sizeof(Letter)); // not exist
	(*letter)->m_next = nullptr;
	(*letter)->m_under = nullptr;
	(*letter)->m_value = 'a';
	(*letter)->m_is_final = FALSE;
	Letter *first_element = (*letter);

	fopen_s(&file, file_name.c_str(), "r");
	if (file)
	{
		while ((c = getc(file)) != EOF)
		{
			if (c != 10)
			{
				add_letter_if_not_exist(letter, c);
				move_to_under(letter);
			}

			else if (c == 10)
			{
				(*letter)->m_is_final = TRUE;
				(*letter) = first_element; // return to start
			}
		}
		fclose(file);
	}
	(*letter) = first_element;
}

void add_letter_if_not_exist(Letter** letter, char c)
{

	// (*letter)!= nullptr && (*letter)->m_next != nullptr : protection
	// if (*letter)->m_value == '\0' : letter doesn't exist

	while ((*letter) != nullptr && (*letter)->m_next != nullptr && (*letter)->m_next->m_value != '\0' && (*letter)->m_value < c && (*letter)->m_value != c)
	{
		move_to_right(letter);
	}

	if ((*letter)->m_value == c) // letter exist : make nothing
		return;

	if ((*letter)->m_value < c && (*letter)->m_next != nullptr)// at end and not exist
	{
		(*letter)->m_next = (Letter *)malloc(sizeof(Letter));
		(*letter)->m_next->m_under = nullptr;
		(*letter)->m_next->m_next = nullptr;
		(*letter)->m_next->m_is_final = FALSE;
		(*letter) = (*letter)->m_next;
		(*letter)->m_value = c;// add letter
		return;
	}

	if ((*letter)->m_value > c) // add on right 
	{
		char right_letter = (*letter)->m_value;

		Letter* new_letter = (Letter *)malloc(sizeof(Letter));
		new_letter->m_value = right_letter;
		new_letter->m_next = (*letter)->m_next;
		new_letter->m_under = (*letter)->m_under;
		new_letter->m_is_final = FALSE;
		(*letter)->m_under = nullptr;

		(*letter)->m_value = c;// add letter
		(*letter)->m_next = new_letter;
		return;
	}

	if ((*letter)->m_is_final == 1)
	{
		move_to_under(letter);
		(*letter)->m_value = c;

		return;
	}

	if ((*letter)->m_value == '\0')
	{
		(*letter)->m_value = c;
		return;
	}

	if ((*letter)->m_next == nullptr || ((*letter)->m_next != nullptr && (*letter)->m_next->m_value == '\0')) // to right
	{
		Letter* new_letter = (Letter *)malloc(sizeof(Letter));
		new_letter->m_value = c;
		new_letter->m_next = nullptr;
		new_letter->m_under = nullptr;
		new_letter->m_is_final = FALSE;

		(*letter)->m_next = new_letter;
		move_to_right(&(*letter));
		return;
	}
	if ((*letter)->m_next->m_value == '\0')
		(*letter)->m_next->m_value = c;
}

char exist(Letter* letter, char c)
{
	while (letter != nullptr && letter->m_next != nullptr && letter->m_next->m_value != '\0' && letter->m_value != c)
	{
		move_to_right(&letter);
	}
	return letter->m_value == c;
}


void move_to_right(Letter** current_letter)
{
	if ((*current_letter) != nullptr && (*current_letter)->m_next != nullptr)
	{
		(*current_letter) = (*current_letter)->m_next;
	}
	else if ((*current_letter) != nullptr)
	{
		(*current_letter)->m_next = (Letter *)malloc(sizeof(Letter)); // not exist
		(*current_letter) = (*current_letter)->m_next;
		(*current_letter)->m_value = '\0';
		(*current_letter)->m_next = nullptr;
		(*current_letter)->m_under = nullptr;
		(*current_letter)->m_is_final = FALSE;
	}
}

void move_to_under(Letter** current_letter)
{
	if ((*current_letter) != nullptr && (*current_letter)->m_under != nullptr) // exist letter
	{
		(*current_letter) = (*current_letter)->m_under;
	}
	else if ((*current_letter) != nullptr)
	{
		(*current_letter)->m_under = (Letter *)malloc(sizeof(Letter)); // not exist
		(*current_letter) = (*current_letter)->m_under;
		(*current_letter)->m_value = '\0';
		(*current_letter)->m_next = nullptr;
		(*current_letter)->m_under = nullptr;
		(*current_letter)->m_is_final = FALSE;
	}
}

void print_tree(Letter * l, char * tab, int index)
{
	if (l == nullptr)
		return;

	tab[index] = l->m_value;
	Letter * temp = l->m_under;

	while (temp != nullptr && temp->m_value != '\0')
	{
		print_tree(temp, tab, ++index);
		tab[index] = '\0';
		index -= 1;
		temp = temp->m_next;
		print_word_tab(tab, 100);
		printf("\n");
		//tab[index] = l->m_value;
	}
}

void print_word_tab(char * tab, int size)
{
	for (int i = 0; i < size && tab[i] != '\0'; i++)
	{
		printf("%c", tab[i]);
	}
}

void print_first_word(Letter* l)
{
	if (!(l != nullptr && l->m_value != '\0'))
		return;

	printf("%c", l->m_value);
	print_first_word(l->m_under);
}

void init_tab(char * tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		tab[i] = '\0';
	}
}


void find_by_letter(char * word, Letter * first_letter, int size_word, int index)
{
	if (word[index + 1] != '\0' && first_letter != nullptr)
		index += 1;

	while (first_letter != nullptr && first_letter->m_value != word[index])
	{
		if (first_letter->m_next != nullptr)
		{
			first_letter = first_letter->m_next;
		}
		else if (first_letter->m_under != nullptr)
		{
			first_letter = first_letter->m_under;
		}
	}

	if (word[index + 1] != '\0')
	{
		printf("%c", word[index]);
		find_by_letter(word, first_letter->m_under, size_word, index);
	}

	else
	{
		print_first_word(first_letter);
		return;
	}

	/*
	if (first_letter != nullptr && first_letter->m_value != '\0' && first_letter->m_value != word[index])
	{
		find_by_letter(word, first_letter->m_next, size_word, index);

		while (first_letter != nullptr && first_letter->m_value != '\0')
		{
			printf("%c", first_letter->m_value);
			first_letter = first_letter->m_under;
			//find_by_letter(word, first_letter->m_under, size_word, index++);
		}
	}*/
}