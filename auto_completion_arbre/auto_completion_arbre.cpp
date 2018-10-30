// auto_completion_arbre.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Letter.h"
#include <vector>

void fill_linked_letter_with_file(std::string file_name, Letter **letter);

// search letter and add if not exist 
void add_letter_if_not_exist(Letter **letter, char c);
// move letter
void move_to_right(Letter** current_letter);
void move_to_under(Letter** current_letter);

// unroll the tree
void unwrap_tree(Letter * letters);

// print words by letter 
void find_word_by_letter(Letter * letters, char c);

void print_to_top(Letter * first_letters);
void set_way(Letter *first_letter, Letter * letters);
void get_final_letter(Letter** letters);
void get_next_way(Letter** letters);
void print_tree(Letter * l, char * tab, int index = 0);

void init_tab(char * tab, int size);
void print_word(char * tab, int size_word);


void find_by_letter(char * word, Letter * first_letter, int size_word, int index);
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
	char test[30] = { 'a','r','b','r','e'};



 }

void fill_linked_letter_with_file(std::string file_name, Letter **letter)
{
	int c;
	FILE* file;
	(*letter) = (Letter *)malloc(sizeof(Letter)); // not exist
	(*letter)->m_next = nullptr;
	(*letter)->m_under = nullptr;
	(*letter)->m_value = 'a';
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

		(*letter)->m_under = nullptr;

		(*letter)->m_value = c;// add letter
		(*letter)->m_next = new_letter;
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
	}
}

void print_tree(Letter * l, char * tab, int index)
{
	if (l == nullptr )
		return;
		
	tab[index] = l->m_value;
	Letter * temp = l->m_under;
	
	while(temp != nullptr && temp->m_value != '\0')
	{
		print_tree(temp, tab, ++index);
		tab[index] = '\0';
		index -= 1;
		temp = temp->m_next;
		print_word(tab, 100);
		printf("\n");
		//tab[index] = l->m_value;
	}
}

void print_word(char * tab, int size)
{
	for(int i =0; i< size && tab[i] != '\0';i++)
	{
		printf("%c", tab[i]);
	}
}

void init_tab(char * tab, int size)
{
	for (int i = 0; i < size ;i++)
	{
		tab[i] = '\0';
	}
}


void find_by_letter(char * word, Letter * first_letter, int size_word, int index)
{
	if (first_letter!= nullptr && first_letter->m_value == '\0')
		return;

	while(first_letter != nullptr && first_letter->m_value != word[index])
	{
		first_letter = first_letter->m_next;
	}

	if(first_letter != nullptr)
		find_by_letter(word, first_letter->m_under, size_word, index++);
}