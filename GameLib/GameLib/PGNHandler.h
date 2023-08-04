#pragma once

#include<unordered_map>

enum class ETag {
    Event,
    Site,
    Date,
    Round,
    White,
    Black,
    Result
};

using String = std::string;
using StringVector = std::vector<String>;
using TagMap = std::unordered_map<ETag, String>;

class PGNHandler
{
public:
    PGNHandler();

    //Setters
    void SetHeader(ETag tag, const String& value);
    void SetPGN(const String& PGN);

    //Save
    void AddMove(const String&);
    void ParseToPGN();
    void SavePGNToFile(const String& filePath);
    
    void Clear();
    void ResetPGN();
    void ResetHeaders();

    // Load
    void ParseFromPGN();
    void LoadPGNFromFile(const String& filePath);
    StringVector GetMoves() const;

private:
    String m_PGN;
    StringVector m_moves;
    TagMap m_headers;
};