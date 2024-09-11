#ifndef Preset_h
#define Preset_h

#include "Arduino.h"
#include "NewQuestion.h"

#define DEFAULT_CODE ""
#define DEFAULT_BANANA -1
#define DEFAULT_WIRE -1
#define DEFAULT_AMQUESTIONS 0

#define MAX_LENGTH 16

#define PLANTTIME 5
#define TIME 120

struct PresetStruct
{
    int8_t bananaConfig;
    int8_t wire;
    uint8_t amQuestions;
    Difficulty questionsDiff;
    unsigned int plantTime;
    unsigned int time;
};

class Preset
{
private:
    int8_t _questionIndex;
    NewQuestion *_question;

public:
    String code;
    int8_t bananaConfig;
    int8_t wire;
    uint8_t amQuestions;
    Difficulty questionsDiff;
    unsigned int plantTime;
    String plantCode;

    unsigned int time;

    Preset(String _code, int8_t _bananaPreset, int8_t _wire, uint8_t _amQuestions, Difficulty _diff, String _plantCode, unsigned int _plantTime, unsigned int _time);
    Preset(String _code, int8_t _bananaPreset, int8_t _wire, unsigned int _plantTime, unsigned int _time);
    Preset(String _code, int8_t _bananaPreset, int8_t _wire, unsigned int _time);
    Preset(uint8_t _amQuestions, Difficulty _diff, String _plantCode, unsigned int _plantTime, unsigned int _time);
    Preset(uint8_t _amQuestions, Difficulty _diff, unsigned int _plantTime, unsigned int _time);
    Preset(uint8_t _amQuestions, Difficulty _diff, String _plantCode, unsigned int _time);
    Preset(uint8_t _amQuestions, Difficulty _diff, unsigned int _time);
    Preset(PresetStruct str, String _code, String _plantCode);
    Preset();

    PresetStruct toStruct();

    Difficulty getQuestionsDiff();
    String getQuestion();
    bool checkQuestion(int answer);
    bool questionsDone();

    void print();
};

#endif