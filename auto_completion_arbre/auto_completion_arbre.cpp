// auto_completion_arbre.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Letter.h"
#include <vector>

#define TRUE 1
#define FALSE 0
void fill_linked_letter_with_file(std::string file_name, Letter **letter);

// search letter and add if not exist 
void add_letter_if_not_exist(Letter **letter, char c);
// move letter
void move_to_right(Letter** current_letter);
void move_to_under(Letter** current_letter);
int main()
{
	Letter* start;
	fill_linked_letter_with_file( "liste_francais.txt",&start);
}

void fill_linked_letter_with_file(std::string file_name, Letter **letter)
{
	int c;
	FILE* file;
	(*letter) = (Letter *)malloc(sizeof(Letter)); // not exist
	(*letter)->m_next = nullptr;
	(*letter)->m_under= nullptr;
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

	while ((*letter)!= nullptr && (*letter)->m_next != nullptr && (*letter)->m_next->m_value != '\0' && (*letter)->m_value < c && (*letter)->m_value != c)
	{
		move_to_right(letter);
	}

	if((*letter)->m_value == c) // letter exist : make nothing
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

	if((*letter)->m_value > c) // add on left 
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

	if ((*letter)->m_next == nullptr || ((*letter)->m_next != nullptr && (*letter)->m_next->m_value == '\0'))
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
	else if((*current_letter) != nullptr)
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