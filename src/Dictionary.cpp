#include "Dictionary.h"
#include <iostream>

Dictionary::Dictionary()
{}

Dictionary::~Dictionary()
{}

bool Dictionary::readRequirements( TextFileReaderInterface& requirementsReader )
{
	firstWord = L"";
	lastWord = L"";

	if( !requirementsReader.open() )
	{
		printf( "сбой при открытии файла с заданными словами\n" );
		return false;
	}

	bool isFault = false;		// сбой при операциях с файлом
	bool isCheckError = false;	// ошибка соответствия данных условиям задания

	bool isReturnedTrue = requirementsReader.readLine( firstWord, isFault );
	if( isReturnedTrue && !isFault )
	{
		requirementsReader.readLine( lastWord, isFault );

		// проверить условия задания для исходного и оконечного слов
		isCheckError = firstWord.empty();									// слова должны быть не пустыми
		isCheckError = ( firstWord.length() != lastWord.length() );			// слова должны иметь одинаковую длину
	}

	if( isFault )
	{
		printf( "сбой при чтении файла с заданными словами\n" );
		return false;
	}
	else if( !isReturnedTrue )
	{
		printf( "неверный формат файла с заданными словами\n" );
		return false;
	}
	else if( isCheckError )
	{
		printf( "исходное и оконечное слова не удовлетворяют всем условиям задания\n" );
		return false;
	}
	else
		return true;
}

bool Dictionary::readDictionary( TextFileReaderInterface& dictionaryReader )
{
	if( firstWord.empty() )
	{
		printf( "исходное и оконечное слова не заданы\n" );
		return false;
	}

	words.clear();

	if( !dictionaryReader.open() )
	{
		printf( "сбой при открытии файла со словарем\n" );
		return false;
	}

	// считать слова из файла в массив, соблюдая условия задания
	int requirementsWordsLength = firstWord.length();	// длина исходного слова, для отсева ненужных слов
	bool isFirstWordFound = false;						// для проверки условия нахождения исходного слова в словаре
	bool isLastWordFound = false;						// для проверки условия нахождения оконечного слова в словаре
	bool isFault = false;								// сбой при операциях с файлом
	std::wstring result = L"";
	while( dictionaryReader.readLine( result, isFault ) )
	{
		// отсеиваем слова с длиной, неравной исходному
		if( (int)result.length() == requirementsWordsLength )
		{
			words.push_back( result );
			if( result == firstWord )
			{
				isFirstWordFound = true;
			}
			else if( result == lastWord )
			{
				isLastWordFound = true;
			}
		}
	}

	// соответствие условиям
	bool isCheckError = !( isFirstWordFound && isLastWordFound );

	if( isFault )
	{
		printf( "сбой при чтении файла со словарём\n" );
		return false;
	}
	else if( isCheckError )
	{
		printf( "слова в файле со словарём не удовлетворяют всем условиям задания\n" );
		return false;
	}
	else
		return true;
}

void Dictionary::resetIterator()
{
	currentWord = words.begin();
}

bool Dictionary::getNextWord( std::wstring& result )
{
	if( currentWord == words.end() )
		return false;

	result = *currentWord;
	currentWord++;
	return true;
}

std::wstring Dictionary::getFirstWord()
{
	return firstWord;
}

std::wstring Dictionary::getLastWord()
{
	return lastWord;
}
