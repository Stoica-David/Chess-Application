#include "PGNHandler.h"
#include "PGNException.h"

#include <string>
#include <fstream>

PGNHandler::PGNHandler()
{
	ResetHeaders();
}


static String ConvertTag(ETag tag)
{
	switch (tag)
	{
	case ETag::Event:
		return "Event";
	case ETag::Site:
		return "Site";
	case ETag::Date:
		return "Date";
	case ETag::Round:
		return "Round";
	case ETag::White:
		return "White";
	case ETag::Black:
		return "Black";
	case ETag::Result:
		return "Result";
	default:
		break;
	}
}

void PGNHandler::SetHeader(ETag tag, const String& value)
{
	m_headers[tag] = "[" + ConvertTag(tag) + " " + value + "]";
}

void PGNHandler::AddMove(const String& newMove)
{
	m_moves.push_back(newMove);
}

void PGNHandler::Clear()
{
	m_headers.clear();

	ResetHeaders();

	m_moves.clear();
}

void PGNHandler::ResetHeaders()
{
	m_headers[ETag::Event] = "[Event \"?\"]";
	m_headers[ETag::Site] = "[Site \"?\"]";
	m_headers[ETag::Date] = "[Date \"????.??.??\"]";
	m_headers[ETag::Round] = "[Round \"?\"]";
	m_headers[ETag::White] = "[White \"?\"]";
	m_headers[ETag::Black] = "[Black \"?\"]";
	m_headers[ETag::Result] = "[Result \"*\"]";
}

void PGNHandler::ParseToPGN()
{
	m_PGN.clear();

	for (const auto& header : m_headers)
	{
		m_PGN += header.second + "\n";
	}

	m_PGN += "\n";

	int moveNumber = 1;

	for (size_t i = 0; i < m_moves.size(); i += 2) {
		m_PGN += std::to_string(moveNumber) + "." + m_moves[i] + " ";

		if (i + 1 < m_moves.size())
		{
			m_PGN += m_moves[i + 1] + " ";
		}
		moveNumber++;
	}

	if (m_headers[ETag::Result] == "[Result 1-0]")
	{
		m_PGN += "1-0";
	}
	else if (m_headers[ETag::Result] == "[Result 0-1]")
	{
		m_PGN += "0-1";
	}
	else if (m_headers[ETag::Result] == "[Result 1/2-1/2]")
	{
		m_PGN += "1/2-1/2";
	}
	else
	{
		m_PGN += "*";
	}
}

void PGNHandler::SavePGNToFile(const String& filePath)
{
	std::ofstream outFile(filePath);

	if (outFile.is_open()) {
		outFile.clear();
		outFile << m_PGN;
		outFile.close();
	}
	else
	{
		throw PGNException("Can't load PGN properly!");
	}
}

void PGNHandler::ResetPGN()
{
	m_PGN = {};
}
