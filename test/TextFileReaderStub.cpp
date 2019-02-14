#include "TextFileReaderStub.h"

TextFileReaderStub::TextFileReaderStub()
{
	currentLine = testContents.begin();
}

TextFileReaderStub::~TextFileReaderStub()
{
	close();
}

bool TextFileReaderStub::open()
{
	// имитация сбоя
	if( faultReason == TextFileReaderStubFaultReason::OpenFault )
		return false;

	currentLine = testContents.begin();
	return true;
}

void TextFileReaderStub::close()
{}

bool TextFileReaderStub::readLine( std::wstring& result, bool& isError )
{
	// имитация сбоя
	if( faultReason == TextFileReaderStubFaultReason::ReadLineFault )
	{
		isError = true;
		return false;
	}

	result = L"";
	isError = false;

	// имитация состояния "достигнут конец файла"
	if( currentLine == testContents.end() )
		return false;

	result = *currentLine;
	currentLine++;
	return true;
}

void TextFileReaderStub::addTestContents( std::wstring testValue )
{
	testContents.push_back( testValue );
}

void TextFileReaderStub::setFaultReason( TextFileReaderStubFaultReason faultReason )
{
	this->faultReason = faultReason;
}

