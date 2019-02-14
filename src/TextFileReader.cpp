#include "TextFileReader.h"
#include <stdio.h>
#include <cstring>
#include <locale>

TextFileReader::TextFileReader( std::string fileName )
	: fileName( fileName )
{}

bool TextFileReader::open()
{
	fileStream.open( fileName );
	if( !fileStream )
	{
		std::cout << "Ошибка при открытии файла " << fileName.c_str() << ": " << strerror( errno ) << std::endl;
		return false;
	}
	return true;
}

void TextFileReader::close()
{
	fileStream.close();
}

bool TextFileReader::readLine( std::wstring& result, bool& isFault )
{
	result = L"";
	isFault = false;

	std::getline( fileStream, result );
	if( fileStream.eof() && result.empty() )
		return false;

	if( fileStream.bad() || fileStream.fail() )
	{
		std::cout << "Ошибка при чтении данных из файла " << fileName.c_str() << std::endl;
		isFault = true;
		return false;
	}
	else
	{
		toUpper( result );
		return true;
	}
}

void TextFileReader::toUpper( std::wstring& str )
{
	std::locale loc;
	std::wstring temp;
	for( std::wstring::size_type i = 0; i < str.length(); i++ )
	{
		temp += std::toupper( str[i], loc );
	}
	str = temp;
}

TextFileReader::~TextFileReader()
{
	close();
}
