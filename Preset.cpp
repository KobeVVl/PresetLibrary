#include "Arduino.h"
#include "Preset.h"

Preset::Preset(String _code, int8_t _bananaConfig, int8_t _wire, uint8_t _amQuestions, Difficulty _diff, String _plantCode, unsigned int _plantTime, unsigned int _time)
{
    _questionIndex = -1;

    code = _code;
    bananaConfig = _bananaConfig;
    wire = _wire;
    amQuestions = _amQuestions;
    questionsDiff = _diff;
    plantTime = _plantTime;
    plantCode = _plantCode;

    time = _time;
}

Preset::Preset(String _code, int8_t _bananaConfig, int8_t _wire, unsigned int _plantTime, unsigned int _time)
{
    _questionIndex = -1;

    code = _code;
    bananaConfig = _bananaConfig;
    wire = _wire;
    amQuestions = DEFAULT_AMQUESTIONS;
    plantTime = _plantTime;
    plantCode = "";

    time = _time;
}

Preset::Preset(String _code, int8_t _bananaConfig, int8_t _wire, unsigned int _time)
{
    _questionIndex = -1;

    code = _code;
    bananaConfig = _bananaConfig;
    wire = _wire;
    amQuestions = DEFAULT_AMQUESTIONS;
    plantTime = PLANTTIME;
    plantCode = "";

    time = _time;
}

Preset::Preset(uint8_t _amQuestions, Difficulty _diff, String _plantCode, unsigned int _plantTime, unsigned int _time)
{
    _questionIndex = 0;

    code = DEFAULT_CODE;
    bananaConfig = DEFAULT_BANANA;
    wire = DEFAULT_WIRE;
    amQuestions = _amQuestions;
    questionsDiff = _diff;

    _question = new NewQuestion(questionsDiff);

    plantTime = _plantTime;
    plantCode = _plantCode;

    time = _time;
}

Preset::Preset(uint8_t _amQuestions, Difficulty _diff, unsigned int _plantTime, unsigned int _time)
{
    _questionIndex = 0;

    code = DEFAULT_CODE;
    bananaConfig = DEFAULT_BANANA;
    wire = DEFAULT_WIRE;
    amQuestions = _amQuestions;
    questionsDiff = _diff;

    _question = new NewQuestion(questionsDiff);

    plantTime = _plantTime;
    plantCode = "";

    time = _time;
}

Preset::Preset(uint8_t _amQuestions, Difficulty _diff, String _plantCode, unsigned int _time)
{
    _questionIndex = 0;

    code = DEFAULT_CODE;
    bananaConfig = DEFAULT_BANANA;
    wire = DEFAULT_WIRE;
    amQuestions = _amQuestions;
    questionsDiff = _diff;

    _question = new NewQuestion(questionsDiff);

    plantTime = PLANTTIME;
    plantCode = _plantCode;

    time = _time;
}

Preset::Preset(uint8_t _amQuestions, Difficulty _diff, unsigned int _time)
{
    _questionIndex = 0;

    code = DEFAULT_CODE;
    bananaConfig = DEFAULT_BANANA;
    wire = DEFAULT_WIRE;
    amQuestions = _amQuestions;
    questionsDiff = _diff;

    _question = new NewQuestion(questionsDiff);

    plantTime = PLANTTIME;
    plantCode = "";

    time = _time;
}

Preset::Preset(PresetStruct *str, String _code, String _plantCode)
{
    code = _code;
    bananaConfig = (*str).bananaConfig;
    wire = (*str).wire;
    amQuestions = (*str).amQuestions;
    questionsDiff = (*str).questionsDiff;

    plantTime = (*str).plantTime;
    plantCode = _plantCode;

    _questionIndex = (amQuestions > 0) ? 0 : -1;
    if (amQuestions > 0)
    {
        _question = new NewQuestion(questionsDiff);
    }

    time = (*str).time;
}

Preset::Preset()
{
    _questionIndex = -1;

    code = DEFAULT_CODE;
    bananaConfig = DEFAULT_BANANA;
    wire = DEFAULT_WIRE;
    amQuestions = DEFAULT_AMQUESTIONS;
    plantTime = PLANTTIME;

    time = TIME;
}

PresetStruct Preset::toStruct()
{
    print();
    char codeStr[MAX_LENGTH];
    code.toCharArray(codeStr, MAX_LENGTH);
    char plantCodeStr[MAX_LENGTH];
    plantCode.toCharArray(plantCodeStr, MAX_LENGTH);
    PresetStruct str = {
        bananaConfig,
        wire,
        amQuestions,
        questionsDiff,
        plantTime,
        time,
    };
    return str;
}
Difficulty Preset::getQuestionsDiff()
{
    return questionsDiff;
}

String Preset::getQuestion()
{
    String question = _question->getQuestion();
    if (question == "0")
    {
        _question = new NewQuestion(questionsDiff);
        return _question->getQuestion();
    }
    return question;
}

bool Preset::checkQuestion(int answer)
{
    bool check = _question->checkAnswer(answer);
    if (check)
    {
        _questionIndex++;
        _question = new NewQuestion(questionsDiff);
    }
    return check;
}

bool Preset::questionsDone()
{
    return amQuestions == _questionIndex;
}

void Preset::print()
{
    Serial.println("Preset: ");
    Serial.print("\t-code: ");
    Serial.println(code);
    Serial.print("\t-banana config: ");
    Serial.println(bananaConfig);
    Serial.print("\t-wire: ");
    Serial.println(wire);
    Serial.print("\t-amount questions: ");
    Serial.println(amQuestions);
    Serial.print("\t-difficulity questions: ");
    Serial.println(questionsDiff);
    Serial.print("\t-plant time: ");
    Serial.println(plantTime);
    Serial.print("\t-plant code: ");
    Serial.println(plantCode);
    Serial.print("\t-time: ");
    Serial.println(time);
}