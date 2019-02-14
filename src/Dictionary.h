#ifndef SRC_DICTIONARY_H_
#define SRC_DICTIONARY_H_

#include "TextFileReader.h"
#include <string>
#include <list>

// предоставляет инструменты для работы с исходными данными и словарем. Обеспечивает считывание из файла
//	исходного и конечного слов, слов словаря, перебор слов в считанном словаре.
class Dictionary
{
public:
	Dictionary();
	virtual ~Dictionary();

	// читает из файла заданные (исходное и конечное) слова. Возвращает false при сбое в операциях с файлом, либо
	//	нарушении граничных условий
	bool readRequirements( TextFileReaderInterface& requirementsReader );

	// читает из файла словарь. Возвращает false при сбое в операциях с файлом, либо
	//	нарушении граничных условий
	bool readDictionary( TextFileReaderInterface& dictionaryReader );

	// сбрасывает указатель на текущее слово в словаре
	void resetIterator();

	// возвращает текущее слово в словаре и передвигает указатель на следующее. Возвращает false, если все слова выбраны
	bool getNextWord( std::wstring& result );

	// getters для firstWord и lastWord
	std::wstring getFirstWord();
	std::wstring getLastWord();

protected:
	std::list< std::wstring > words;						// словарь
	std::list< std::wstring >::iterator currentWord;		// указатель на текущее слово в словаре
	std::wstring firstWord = L"";							// исходное слово
	std::wstring lastWord = L"";							// конечное слово
};

#endif /* SRC_DICTIONARY_H_ */
