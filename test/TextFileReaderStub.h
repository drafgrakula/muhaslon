// тестовый стаб для построчного чтения из текстового файла

#ifndef TEST_TEXTFILEREADERSTUB_H_
#define TEST_TEXTFILEREADERSTUB_H_

#include "TextFileReader.h"
#include <list>

// задаёт причину имитированного сбоя при использовании стаба
enum TextFileReaderStubFaultReason
{
	None,			// все операции со стабом пройдут успешно
	OpenFault,		// имитация сбоя при открытии файла
	ReadLineFault	// имитация сбоя при чтении строки из файла
};

class TextFileReaderStub : public TextFileReaderInterface
{
public:
	TextFileReaderStub();
	bool open();
	void close();
	bool readLine( std::wstring& result, bool& isFault );
	virtual ~TextFileReaderStub();

	// добавляет строку в тестовое содержимое testContents. Используется для тестирования
	void addTestContents( std::wstring testValue );

	// setter для faultReason
	void setFaultReason( TextFileReaderStubFaultReason faultReason );

private:
	std::list< std::wstring > testContents;				// заменяет собой содержимое реального файла
	std::list< std::wstring >::iterator currentLine;	// текущая считываемая строка в testContents
	TextFileReaderStubFaultReason faultReason
		= TextFileReaderStubFaultReason::None;	// при имитации сбоя, задаваемого в setFaultReason(), содержит причину сбоя
};

#endif /* TEST_TEXTFILEREADERSTUB_H_ */
