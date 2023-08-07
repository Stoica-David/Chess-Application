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
    //Constructor
    PGNHandler();

    //Setters
    void SetHeader(ETag tag, const String& value);
    void SetPGN(const String& PGN);

    //Getters
    String GetPGN()const;
    StringVector GetMoves() const;

    //Save 
    void AddMove(const String&);
    void ParseToPGN();
    void SavePGNToFile(const String& filePath);
    
    //Load
    void ParseFromPGN();
    void LoadPGNFromFile(const String& filePath);
    
    //Check GameOver
    bool IsOverWhite();
    bool IsOverBlack();
    bool IsDraw();
    
    //Other methods
    void Clear();
    void ResetPGN();
    void ResetHeaders();

private:
    //Regex related
    void HeaderRegex();
    void CommentRegex();
    void UselessCharRegex();

    //Save related
    void AddHeaders();
    void AddEndGame();

private:
    String m_PGN;
    StringVector m_moves;
    TagMap m_headers;
};