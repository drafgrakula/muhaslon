// текстовый файл, используемый только для чтения построчно

#ifndef SRC_TEXTFILEREADER_H_
#define SRC_TEXTFILEREADER_H_

#include <string>
#include <iostream>
#include <fstream>

// интерфейс для работы с читателем текстового файла, используется для создания рабочей реализации и тестового стаба
class TextFileReaderInterface
{
public:
	// открывает файл. Возвращает false при ошибке.
	virtual bool open() = 0;

	// закрывает файл
	virtual void close() = 0;

	// читает очередную строку из файла в result. Возвращает false, если достигнут конец файла или произошёл сбой
	//	Флаг сбоя устанавливается в isFault
	virtual bool readLine(
			std::wstring& result,
			bool& isFault				// возвращает true, если при чтении произошел сбой
			) = 0;

	virtual ~TextFileReaderInterface()
	{};
};

// рабочая реализация
class TextFileReader : public TextFileReaderInterface
{
public:
	TextFileReader( std::string fileName );
	bool open();
	void close();
	bool readLine( std::wstring& result, bool& isFault );
	virtual ~TextFileReader();

protected:
	std::string fileName;
	std::wifstream fileStream;

	// возводит строку в верхний регистр
	void toUpper( std::wstring& str );
};

#endif /* SRC_TEXTFILEREADER_H_ */
