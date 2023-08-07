#include "PGNHandler.h"
#include "PGNException.h"

#include <string>
#include <fstream>
#include <sstream>
#include <regex>

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

void PGNHandler::SetPGN(const String& PGN)
{
	m_PGN = PGN;
}

String PGNHandler::GetPGN() const
{
	return m_PGN;
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

void PGNHandler::ParseFromPGN()
{
	std::regex headerRegex("\\[.*?\\]\n");
	std::regex commentRegex("\\{[^}]*\\}");
	m_PGN = std::regex_replace(m_PGN, headerRegex, "");
	m_PGN = std::regex_replace(m_PGN, commentRegex, "");
	m_PGN = std::regex_replace(m_PGN, std::regex("\\n"), " ");
	m_PGN = std::regex_replace(m_PGN, std::regex("\\b\\d+\\.\\ *|[+#x*]"), "");

	m_moves.clear();

	std::regex moveRegex(R"(\b([KQRBNP])?([a-h]?[1-8]?)?([x:])?([a-h][1-8])(=?[QRBN]?)?([+#]?)\b|O-O-O|O-O)");

	// Create an iterator to find all matches in the PGN string
	std::sregex_iterator it(m_PGN.begin(), m_PGN.end(), moveRegex);
	std::sregex_iterator end;

	for (; it != end; ++it) 
	{
		std::smatch match = *it;

		String moveString = match[0].str();

		m_moves.push_back(moveString);
	}
}

void PGNHandler::LoadPGNFromFile(const String& filePath)
{
	std::ifstream inFile(filePath);

	if (inFile.is_open()) {
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		m_PGN = buffer.str();
		inFile.close();
	}
	else {
		throw PGNException("Error: Unable to open the file for reading.");
	}
}

bool PGNHandler::IsOverWhite()
{
	return m_PGN.rfind("1-0") < m_PGN.size();
}

bool PGNHandler::IsOverBlack()
{
	return m_PGN.rfind("0-1") < m_PGN.size();
}

bool PGNHandler::IsDraw()
{
	return m_PGN.rfind("1/2-1/2") < m_PGN.size();
}

StringVector PGNHandler::GetMoves() const
{
	return m_moves;
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
