//Js ampv2 C++ port by Glacc
//20-02-12

//Amiga module player by Glacc
//
//Unsupported effects :
//
//	E3x	Set glissando on/off
//	E4x Set vibrato waveform
//	E5x	Set finetune value
//	E7x Set tremolo waveform
//	EFx	Invert loop
//

#define SMP_RATE 44100
#define BUFFER_SIZE 4096
#define STEREOSEP_AMIGA 0.5
#define STEREOSEP_EXT 1
#define VOLRAMPING_SPD 10

#define NOTE_SIZE 4
#define ROW_SIZE NOTE_SIZE*NumOfChannels
#define PATTERN_SIZE ROW_SIZE*64

#define AMIGAFREQ 7093790

#define TOINT_SCL 32768.0
#define INT_ACC 15

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <time.h>

static uint32_t SamplingRate = SMP_RATE;
static float StereoSep = STEREOSEP_AMIGA;
static bool SongLoaded = false;
static bool Playing = false;
static bool Interpolation = true;
static bool AmigaFreqLimits = true;

static uint8_t MasterVol = 255;

static char SongName[20];
static uint8_t NumOfSamples, NumOfChannels, NumOfPatterns, ResetPos;
static int16_t Tick, CurrentRow, CurrentPos, SongLeng;
static int16_t PatBreak, PatJump, PatDelay;
static int16_t PatRepeat, RepeatPos, RepeatTo;
static uint8_t Speed, Tempo;
static double Timer, TimePerSample;
static double StartTime, EndTime, ExcuteTime;

static const uint16_t ProTrackerTunedPeriods[12*16] = {
	1712,1616,1524,1440,1356,1280,1208,1140,1076,1016,960,907,
	1700,1604,1514,1430,1348,1274,1202,1134,1070,1010,954,900,
	1688,1592,1504,1418,1340,1264,1194,1126,1064,1004,948,894,
	1676,1582,1492,1408,1330,1256,1184,1118,1056,996,940,888,
	1664,1570,1482,1398,1320,1246,1176,1110,1048,990,934,882,
	1652,1558,1472,1388,1310,1238,1168,1102,1040,982,926,874,
	1640,1548,1460,1378,1302,1228,1160,1094,1032,974,920,868,
	1628,1536,1450,1368,1292,1220,1150,1086,1026,968,914,862,
	1814,1712,1616,1524,1440,1356,1280,1208,1140,1076,1016,960,
	1800,1700,1604,1514,1430,1350,1272,1202,1134,1070,1010,954,
	1788,1688,1592,1504,1418,1340,1264,1194,1126,1064,1004,948,
	1774,1676,1582,1492,1408,1330,1256,1184,1118,1056,996,940,
	1762,1664,1570,1482,1398,1320,1246,1176,1110,1048,988,934,
	1750,1652,1558,1472,1388,1310,1238,1168,1102,1040,982,926,
	1736,1640,1548,1460,1378,1302,1228,1160,1094,1032,974,920,
	1724,1628,1536,1450,1368,1292,1220,1150,1086,1026,968,914
	};

static const uint16_t PeriodTableMod[37*16+14] = {
    856,808,762,720,678,640,604,570,538,508,480,453,
    428,404,381,360,339,320,302,285,269,254,240,226,
    214,202,190,180,170,160,151,143,135,127,120,113,0,
    850,802,757,715,674,637,601,567,535,505,477,450,
    425,401,379,357,337,318,300,284,268,253,239,225,
    213,201,189,179,169,159,150,142,134,126,119,113,0,
    844,796,752,709,670,632,597,563,532,502,474,447,
    422,398,376,355,335,316,298,282,266,251,237,224,
    211,199,188,177,167,158,149,141,133,125,118,112,0,
    838,791,746,704,665,628,592,559,528,498,470,444,
    419,395,373,352,332,314,296,280,264,249,235,222,
    209,198,187,176,166,157,148,140,132,125,118,111,0,
    832,785,741,699,660,623,588,555,524,495,467,441,
    416,392,370,350,330,312,294,278,262,247,233,220,
    208,196,185,175,165,156,147,139,131,124,117,110,0,
    826,779,736,694,655,619,584,551,520,491,463,437,
    413,390,368,347,328,309,292,276,260,245,232,219,
    206,195,184,174,164,155,146,138,130,123,116,109,0,
    820,774,730,689,651,614,580,547,516,487,460,434,
    410,387,365,345,325,307,290,274,258,244,230,217,
    205,193,183,172,163,154,145,137,129,122,115,109,0,
    814,768,725,684,646,610,575,543,513,484,457,431,
    407,384,363,342,323,305,288,272,256,242,228,216,
    204,192,181,171,161,152,144,136,128,121,114,108,0,
    907,856,808,762,720,678,640,604,570,538,508,480,
    453,428,404,381,360,339,320,302,285,269,254,240,
    226,214,202,190,180,170,160,151,143,135,127,120,0,
    900,850,802,757,715,675,636,601,567,535,505,477,
    450,425,401,379,357,337,318,300,284,268,253,238,
    225,212,200,189,179,169,159,150,142,134,126,119,0,
    894,844,796,752,709,670,632,597,563,532,502,474,
    447,422,398,376,355,335,316,298,282,266,251,237,
    223,211,199,188,177,167,158,149,141,133,125,118,0,
    887,838,791,746,704,665,628,592,559,528,498,470,
    444,419,395,373,352,332,314,296,280,264,249,235,
    222,209,198,187,176,166,157,148,140,132,125,118,0,
    881,832,785,741,699,660,623,588,555,524,494,467,
    441,416,392,370,350,330,312,294,278,262,247,233,
    220,208,196,185,175,165,156,147,139,131,123,117,0,
    875,826,779,736,694,655,619,584,551,520,491,463,
    437,413,390,368,347,328,309,292,276,260,245,232,
    219,206,195,184,174,164,155,146,138,130,123,116,0,
    868,820,774,730,689,651,614,580,547,516,487,460,
    434,410,387,365,345,325,307,290,274,258,244,230,
    217,205,193,183,172,163,154,145,137,129,122,115,0,
    862,814,768,725,684,646,610,575,543,513,484,457,
    431,407,384,363,342,323,305,288,272,256,242,228,
    216,203,192,181,171,161,152,144,136,128,121,114,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};

struct Channel {
    uint32_t Delta;
    uint8_t Note;
    int16_t Period;
    int16_t TargetPeriod;
    bool Slid;
    uint16_t PeriodOffset;
    int16_t ArpeggioPeriod;
    uint8_t Sample;
    uint8_t SampleOld;
    uint32_t Pos;
    bool Looping;
    uint16_t Offset;
    uint16_t OffsetOld;
    char Volume;
    int8_t VolFac;
    float VolFinal;
    uint8_t Effect;
    uint8_t LastEffect;
    uint8_t Para;
    uint8_t LastPara;
    int16_t Pan;
    float VibratoPos;
    uint8_t VibratoAmp;
    float TremorPos;
    uint8_t TremorAmp;
    int16_t ParaSlide;
    uint8_t ParaVibrato;
    uint8_t ParaTremor;
    int16_t Delay;
    int16_t DelayCut;
    uint8_t RetrigNote;
    uint8_t RetrigSample;
    int16_t RetrigPeriod;
    uint8_t RetrigEffect;
    uint8_t RetrigPara;
    bool Muted;
};

struct Sample {
    char Name[22];
    uint16_t Length;
    char Finetune;
    uint8_t Volume;
    uint16_t RepeatPoint;
    uint16_t RepeatLeng;
    uint64_t Addr;
};

static uint8_t Order[128];
static Sample Samples[31];
static Channel Channels[32];
static uint32_t TotalSampleSize = 0;
int8_t*SampleData;
uint8_t*PatternData;
uint8_t*SongData;
static int16_t *SndBuffer[2];

#define Ch Channels[i]

static void RstChannels(uint8_t Num) {
    int i = 0;
    while (i < Num) {
        Ch.Delta = 0;
        Ch.Note = 0;
        Ch.Period = 428;
        Ch.TargetPeriod = 428;
        Ch.Slid = false;
        Ch.PeriodOffset = 0;
        Ch.ArpeggioPeriod = 0;
        Ch.Sample = 32;
        Ch.SampleOld = 32;
        Ch.Pos = 0;
        Ch.Looping = false;
        Ch.Offset = 0;
        Ch.OffsetOld = 0;
        Ch.Volume = 0;
        Ch.VolFac = 0;
        Ch.VolFinal = 0;
        Ch.Effect = 0;
        Ch.LastEffect = 0;
        Ch.Para = 0;
        Ch.LastPara = 0;
        Ch.Pan = -1;
        Ch.VibratoPos = 0;
        Ch.VibratoAmp = 0;
        Ch.TremorPos = 0;
        Ch.TremorAmp = 0;
        Ch.ParaSlide = 0;
        Ch.ParaVibrato = 0;
        Ch.ParaTremor = 0;
        Ch.Delay = -1;
        Ch.DelayCut = 0;
        Ch.RetrigNote = 0;
        Ch.RetrigSample = 0;
        Ch.RetrigPeriod = 428;
        Ch.Muted = false;

        i ++ ;
    }
}

extern "C" __declspec(dllexport) void MPSetPos(uint8_t Pos) {
    if ((Pos < 0) | (Pos > SongLeng)) return;
    RstChannels(NumOfChannels);
    Tick = 0;
    CurrentPos = Pos;
    CurrentRow = -1;
}

static inline void ClearSamples() {
    int i = 0;
    while (i < 31) {
        int j = 0;
        while (j < 22) {
            Samples[i].Name[j] = 0;
            j ++ ;
        }
        Samples[i].Length = 0;
        Samples[i].Finetune = 0;
        Samples[i].Volume = 0;
        Samples[i].RepeatPoint = 0;
        Samples[i].RepeatLeng = 0;
        Samples[i].Addr = 0;
        i ++ ;
    }
}

extern "C" __declspec(dllexport) void MPPlayPause(bool Value) {
    Playing = Value;
}

extern "C" __declspec(dllexport) void MPResetModule() {
    Playing = true;

    Tick = 0;
    Tempo = 125;
    Speed = 6;

    CurrentRow = -1;
    CurrentPos = 0;
    PatBreak = -1;
    PatJump = -1;
    PatDelay = 0;

    PatRepeat = 0;
    RepeatPos = 0;
    RepeatTo = -1;

    SongLoaded = true;

    RstChannels(NumOfChannels);
}

#define NOTEPTR uint8_t *Pointer = PatternData + PATTERN_SIZE*PatNum + ROW_SIZE*Row + NOTE_SIZE*Col;

static inline uint16_t GetNotePeriod(uint8_t PatNum, uint8_t Row, uint8_t Col) {
    NOTEPTR
    return ((((uint16_t)(*Pointer)<<8)&0x0F00) | ((uint16_t)(*(Pointer + 1))));
}

static inline uint8_t GetNoteData(uint8_t PatNum, uint8_t Row, uint8_t Col, uint8_t Num) {
    NOTEPTR
    switch (Num) {
        default:    //Sample number
            return (((*Pointer)&0xF0) | (((*(Pointer + 2))>>4)&0x0F));
            break;
        case 1:     //Effect number
            return ((*(Pointer + 2))&0x0F);
            break;
        case 2:     //Parameter
            return (*(Pointer + 3));
            break;
    }
}

extern "C" __declspec(dllexport) bool MPLoadModule(uint8_t *SongDataOrig, uint32_t SongDataLeng, bool UsingInterpolation, bool IsSTK = false, float TargetStereoSep = 0) {
    MPResetModule();

    MasterVol = 255;

    int i, j, k;
    uint32_t SongDataOfs = 0;

    Interpolation = UsingInterpolation;

    if (SongData != NULL)
        free(SongData);

    SongData = (uint8_t *)malloc(SongDataLeng);
    memcpy(SongData, SongDataOrig, SongDataLeng);

    if (IsSTK)
        NumOfSamples = 15;
    else
        NumOfSamples = 31;

    //Get song name
    while (SongDataOfs < 20) {
        SongName[SongDataOfs] = SongData[SongDataOfs];
        SongDataOfs ++ ;
    }

    //Get sample info
    ClearSamples();

    TotalSampleSize = 0;
    i = 0;
    while (i < NumOfSamples) {
        SongDataOfs = 20 + i*30;

        //Sample name
        j = 0;
        while (j < 22) {
            Samples[i].Name[j] = SongData[SongDataOfs+j] ++ ;
            j ++ ;
        }

        //Sample length
        uint16_t Leng = Samples[i].Length = 2*(((((uint16_t)SongData[SongDataOfs+22])<<8)&0xFF00) | SongData[SongDataOfs+23]);

        Samples[i].Finetune = SongData[SongDataOfs+24]&0x0F; //Sample finetune
        Samples[i].Volume = SongData[SongDataOfs+25];   //Sample volume

        //Sample loop points
        Samples[i].RepeatPoint = 2*(((((uint16_t)SongData[SongDataOfs+26])<<8)&0xFF00) | SongData[SongDataOfs+27]);
        Samples[i].RepeatLeng = 2*(((((uint16_t)SongData[SongDataOfs+28])<<8)&0xFF00) | SongData[SongDataOfs+29]);

        //Sample address
        Samples[i].Addr = TotalSampleSize;
        TotalSampleSize += Leng;

        i ++ ;
    }

    SongDataOfs += 30;
    SongLeng = SongData[SongDataOfs];

    NumOfPatterns = 0;

    SongDataOfs += 2;

    i = 0;
    while (i < 128) {
        uint8_t PatternNum = SongData[SongDataOfs];
        NumOfPatterns = PatternNum > NumOfPatterns ? PatternNum : NumOfPatterns;
        Order[i] = PatternNum;
        SongDataOfs ++ ;
        i ++ ;
    }

    //Default settings
    NumOfChannels = 4;
    StereoSep = STEREOSEP_AMIGA;
    AmigaFreqLimits = true;

    if (!IsSTK) {
        //Module tag
        static const char FT2Tags[32][5] = {
            "1CHN", "2CHN", "3CHN", "4CHN", "5CHN", "6CHN", "7CHN", "8CHN",
            "9CHN", "10CH", "11CH", "12CH", "13CH", "14CH", "15CH", "16CH",
            "17CH", "18CH", "19CH", "20CH", "21CH", "22CH", "23CH", "24CH",
            "25CH", "26CH", "27CH", "28CH", "29CH", "30CH", "31CH", "32CH"
            };

        static char Tag[4] = "";

        i = 0;
        while (i < 4) {
            Tag[i] = SongData[SongDataOfs + i];
            i ++ ;
        }

        if (!strncmp(Tag, "CD81", 4) || !strncmp(Tag, "OCTA", 4) || !strncmp(Tag, "FLT8", 4)) {
            NumOfChannels = 8;
            AmigaFreqLimits = false;
        }

        i = 0;
        while (i < 32) {
            if (!strncmp(Tag, FT2Tags[i], 4)) {
                NumOfChannels = i + 1;
                AmigaFreqLimits = false;
            }
            i ++ ;
        }

        //First byte of pattern data
        SongDataOfs += 4;
    }

    PatternData = SongData + SongDataOfs;

    i = 0;
    while (i < NumOfPatterns) {
        j = 0;
        while (j < 64) {
            k = 0;
            while (k < NumOfChannels) {
                uint16_t NotePeriod = GetNotePeriod(i, j, k);
                if (((NotePeriod > 856) | (NotePeriod < 113)) && (NotePeriod != 0))
                    AmigaFreqLimits = false;

                k ++ ;
            }
            j ++ ;
        }
        i ++ ;
    }

    SongDataOfs += PATTERN_SIZE*(NumOfPatterns+1);

    if (SongDataOfs + TotalSampleSize > SongDataLeng)
        return false;

    SampleData = (int8_t*)(SongData + SongDataOfs);

    ResetPos = 0;
    if (AmigaFreqLimits) {
        if (SongData[951] != 127) ResetPos = SongData[951];
        StereoSep = STEREOSEP_EXT;
    }

    if ((TargetStereoSep >= 0) && (TargetStereoSep <= 1))
        StereoSep = TargetStereoSep;

    TimePerSample = 1.0/SamplingRate;

    RstChannels(NumOfChannels);

    return true;
}

static inline void NextRow() {
    if (PatDelay == 0) {
		CurrentRow ++ ;
		if (PatBreak >= 0) {
			CurrentRow = PatBreak;
			PatBreak = RepeatTo = -1;
			PatRepeat = RepeatPos = 0;
			CurrentPos ++ ;
		} else if (PatJump >= 0) {
			CurrentPos = PatJump;
			CurrentRow = PatRepeat = RepeatPos=0;
			RepeatTo = PatJump = -1;
		} else if (RepeatTo >= 0) {
			CurrentRow = RepeatTo;
			RepeatTo = -1;
		} else if (CurrentRow >= 64) {
			CurrentRow = PatRepeat = RepeatPos = 0;
			RepeatTo = -1;
			CurrentPos ++ ;
		}
		if (CurrentPos >= SongLeng)
            CurrentPos = ResetPos;

        int i = 0;
		while (i < NumOfChannels) {
			uint16_t NotePeriod = GetNotePeriod(Order[CurrentPos], CurrentRow, i);
			uint8_t NoteSample = GetNoteData(Order[CurrentPos], CurrentRow, i, 0);
			uint8_t Effect = GetNoteData(Order[CurrentPos], CurrentRow, i, 1);
			uint8_t Para = GetNoteData(Order[CurrentPos], CurrentRow, i, 2);

			int j = 0;
			uint16_t NoteRange = (AmigaFreqLimits ? 37 : 85);
			while (j < NoteRange) {
				if ((NotePeriod >= PeriodTableMod[j]) && AmigaFreqLimits) {
					Ch.Note = j;
					break;
				} else if ((NotePeriod >= (ProTrackerTunedPeriods[j%12] << 1) >> (uint8_t)(j/12)) && !AmigaFreqLimits) {
					Ch.Note = j;
					break;
				}
				j++;
			}

			if (Effect != 0 || Para != 0) {
                Ch.LastEffect = Effect;
                Ch.LastPara = Para;
			}

			Ch.Effect = Effect;
			Ch.Para = Para;

			if (!(Ch.LastEffect == 14 && ((Ch.LastPara&0xF0) >> 4) == 13))
                Ch.Delay = -1;

			if ((Effect != 14) || (Effect == 14 && ((Para&0xF0) >> 4) != 13)) {
				if (NoteSample != 0) {
					Ch.Offset = 0;
					/*Ch.VolFinal = */Ch.Volume = Samples[NoteSample - 1].Volume;
					if (Effect != 3 && Effect != 5)
                        Ch.SampleOld = NoteSample - 1;

					if ((Effect != 3) && (Effect != 5) && (Effect != 9) && !Ch.Slid)
                        Ch.Sample = Ch.SampleOld;
				}
				if (NotePeriod != 0) {
					int8_t Finetune = 0;
					if ((Effect != 3) && (Effect != 5))
                        Ch.Sample = Ch.SampleOld;

					if (Samples[Ch.Sample].Length != 0)
                        Finetune = Samples[Ch.Sample].Finetune;

					if (AmigaFreqLimits) {
						Ch.PeriodOffset = Ch.Note + Finetune*37;
						Ch.TargetPeriod = PeriodTableMod[Ch.PeriodOffset];
					} else Ch.TargetPeriod = (ProTrackerTunedPeriods[Ch.Note%12 + Finetune*12] << 1) >> ((uint8_t)(Ch.Note/12) + (AmigaFreqLimits ? 1 : 0));

					if ((Effect != 9) && (Effect != 3) && (Effect != 5))
                        Ch.Pos = Ch.Offset<<INT_ACC;

					if ((Effect != 3) && (Effect != 5)) {
						Ch.Slid = false;
						if ((Effect == 0) && (Para!=0))
                            Ch.ArpeggioPeriod = Ch.Period = Ch.TargetPeriod;
						else {
							Ch.Period = Ch.TargetPeriod;
							Ch.ArpeggioPeriod = 0;
						}
					}
				}
				if (((NoteSample != 0) || (NotePeriod != 0))&& (Effect == 9)) {
					Ch.Offset=Para*256;
					if (Ch.Offset != 0)
                        Ch.OffsetOld = Ch.Offset;

					if (NotePeriod != 0)
                        Ch.Pos = Ch.OffsetOld<<INT_ACC;
				}
			} else {
				Ch.Delay = Para&0xF;
				Ch.RetrigNote = Ch.Note;
				Ch.RetrigSample = NoteSample;
				Ch.RetrigPeriod = NotePeriod;
				Ch.RetrigEffect = Effect;
				Ch.RetrigPara = Para;
			}

			if ((Effect != 0) || (Para == 0))   //0XX
                Ch.ArpeggioPeriod = 0;

			if ((Effect == 3) && (Para != 0))   //3XX
                Ch.ParaSlide = Para;

			if (Effect == 4) {  //4XX
				if ((Para&0xF)>0)
                    Ch.ParaVibrato=(Ch.ParaVibrato&0xF0)+(Para&0xF);

				if (((Para&0xF0)>>4)>0)
                    Ch.ParaVibrato=(Ch.ParaVibrato&0xF)+(Para&0xF0);
			}
			if (Effect == 7) {  //7XX
				if ((Para&0xF)>0)
                    Ch.ParaTremor = (Ch.ParaTremor&0xF0)+(Para&0xF);

				if (((Para&0xF0)>>4)>0)
                    Ch.ParaTremor = (Ch.ParaTremor&0xF)+(Para&0xF0);
			}
			if ((Effect == 8) && !AmigaFreqLimits)  //8XX
                Ch.Pan = Para<<1;

			if (Effect == 11) //BXX
                PatJump = Para;

			if (Effect == 12) {//CXX
                Ch.Volume = Para;
                if (NoteSample != 0)
                    Ch.VolFac = Para;
            }

			if (Effect==13) //DXX
                PatBreak=(Para>>4)*10+Para%0xF;

			if ((Effect == 14) && (((Para&0xF0)>>4) == 6)) {    //E6X
				if (((Para&0xF) == 0) && (RepeatPos < CurrentRow)) {
					RepeatPos = CurrentRow;
					PatRepeat = 0;
				} else if (PatRepeat < (Para&0xF)) {
					PatRepeat ++ ;
					RepeatTo = RepeatPos;
				}
			}
			if ((Effect == 14) && (((Para&0xF0)>>4) == 9)) {    //E9X
				Ch.Delay = Para&0xF;
				Ch.RetrigNote = Ch.Note;
				Ch.RetrigSample = NoteSample;
				Ch.RetrigPeriod = NotePeriod;
				Ch.RetrigEffect = Effect;
				Ch.RetrigPara = Para;
			}
			if ((Effect == 14) && (((Para&0xF0)>>4) == 14)) //EDX
                PatDelay = Para&0x0F;

			if (Effect == 15 && Para != 0) {   //FXX
				if (Para < 32)
                    Speed = Para;
				else Tempo = Para;
			}

			if (Ch.Delay > -1)
                Ch.Delay--;

			i++;
		}
	} else {
		PatDelay--;
	}
}

#define PI 3.1415926535897932384626433832795

static inline void UpdateChannelInfo() {
    int i = 0;
    while (i < NumOfChannels) {
        Ch.Delta = (uint32_t)((AMIGAFREQ/((Ch.ArpeggioPeriod != 0 ? Ch.ArpeggioPeriod : Ch.Period) + Ch.VibratoAmp*sin(Ch.VibratoPos/32*PI)*2)/2/SamplingRate)*TOINT_SCL);
        Ch.VolFac = (int8_t)(Ch.Volume + Ch.TremorAmp*sin(Ch.TremorPos/32*PI)*4);
        i ++ ;
    }
}

static inline void NextTick() {
    int i = 0;
    Tick ++ ;

	if (Tick >= Speed) {
		Tick = 0;
		NextRow();
		goto End;
	}

	while (i < NumOfChannels) {
		uint8_t Effect = Ch.Effect;
		uint8_t Para = Ch.Para;
		if (Ch.Delay <= -1) {
            int8_t ArpNote1 = Para >> 4;
            int8_t ArpNote2 = Para & 0xF;

            //0XX
			if (Effect == 0 && Para != 0) {
				if (AmigaFreqLimits) {
                    int8_t Arpeggio[3] = {0, ArpNote1, ArpNote2};
                    Ch.ArpeggioPeriod = MAX(108, MIN(907, PeriodTableMod[Ch.PeriodOffset+Arpeggio[Tick%3]]));
				} else {
				    int8_t Arpeggio[3] = {0, ArpNote2, ArpNote1};
					//uint8_t ArpeggioNote = (Ch.Note + Arpeggio[(Tick+1)%3]);
					uint8_t ArpeggioNote = (Ch.Note + Arpeggio[Tick%3]);
					Ch.ArpeggioPeriod = (ProTrackerTunedPeriods[Samples[Ch.Sample].Finetune*12 + ArpeggioNote%12] << 1) >> ((uint8_t)(ArpeggioNote/12) + (AmigaFreqLimits ? 1 : 0));
				}
			} else {
				Ch.ArpeggioPeriod = 0;
			}

			//1XX, 2XX, 3XX, 5XX
			if (Effect == 1)
				Ch.Period -= Para;
			else if (Effect == 2)
				Ch.Period += Para;
			else if ((Effect == 3) || (Effect == 5)) {
				Ch.Slid = true;
				if (Ch.Period > Ch.TargetPeriod)
                    Ch.Period -= Ch.ParaSlide;
				else if (Ch.Period < Ch.TargetPeriod)
                    Ch.Period += Ch.ParaSlide;
				if (abs((int16_t)Ch.Period - (int16_t)Ch.TargetPeriod) < Ch.ParaSlide) {
					Ch.Period = Ch.TargetPeriod;
					Ch.Slid = false;
				}
			}

			//4XX, 6XX
			if ((Effect == 4) || (Effect == 6)) {
				Ch.VibratoAmp = Ch.ParaVibrato&0xF;
				Ch.VibratoPos += (Ch.ParaVibrato&0xF0)>>4;
			} else Ch.VibratoPos=0;

			//5XX, 6XX, AXX
			if ((Effect == 5) || (Effect == 6) || (Effect == 10)) {
				if (Para < 16)
                    Ch.Volume= MAX(0, Ch.Volume-Para);

				else Ch.Volume=MIN(64, Ch.Volume + (Para>>4));
			}

            //7XX
			if (Effect == 7) {
				Ch.TremorAmp = Ch.ParaTremor&0xF;
				Ch.TremorPos += (Ch.ParaTremor&0xF0)>>4;
			} else Ch.TremorPos = 0;

			//CXX
			if (Effect == 12)
                Ch.Volume = Para;

			//EXX
			if (Effect == 14) {
				uint8_t Effect2 = Para>>4;
				uint8_t Para2 = Para&0xF;
				if (Tick == 1) {
					if (Effect2 == 1)
                        Ch.Period -= Para2;

					if (Effect2 == 2)
                        Ch.Period += Para2;

					if (Effect2 == 10)
                        Ch.Volume = MIN(64, Ch.Volume + Para2);

					if (Effect2 == 11)
                        Ch.Volume = MAX(0, Ch.Volume - Para2);
				}
				if ((Effect2 == 12) && (Tick == Para2)) Ch.Volume = 0;
			}
			if (AmigaFreqLimits) Ch.Period = MAX(108, MIN(907, Ch.Period));
		} else {
			if (Ch.Delay > -1) Ch.Delay -- ;
			if (Ch.Delay < 1) {
				Effect = Ch.RetrigEffect;
				Para = Ch.RetrigPara;
				if (Ch.RetrigSample != 0) {
					Ch.Offset = 0;
					/*Ch.VolFinal = */Ch.Volume = Samples[Ch.RetrigSample - 1].Volume;

					if (Effect != 3)
                        Ch.SampleOld = Ch.RetrigSample-1;

					if ((Effect != 3) && (Effect != 5) && (Effect != 9) && (!Ch.Slid))
                        Ch.Sample = Ch.SampleOld;
				}
				if (Ch.RetrigPeriod != 0) {
					int8_t Finetune = 0;
					if ((Effect != 3) && (Effect != 5))
                        Ch.Sample = Ch.SampleOld;

					if (Samples[Ch.Sample].Length != 0)
                        Finetune = Samples[Ch.Sample].Finetune;

					if (AmigaFreqLimits) {
						Ch.PeriodOffset = Ch.RetrigNote + Finetune*37;
						Ch.TargetPeriod = PeriodTableMod[Ch.PeriodOffset];
					} else Ch.TargetPeriod = (ProTrackerTunedPeriods[Ch.RetrigNote%12 + Finetune*12] << 1) >> ((uint8_t)(Ch.RetrigNote/12) + (AmigaFreqLimits ? 1 : 0));

					if ((Effect != 9) && (Effect != 3) && (Effect != 5))
                        Ch.Pos=Ch.Offset<<INT_ACC;

					if ((Effect != 3) && (Effect != 5)) {
						Ch.Slid = false;
						if ((Effect == 0) && (Para != 0))
                            Ch.ArpeggioPeriod = Ch.Period = Ch.TargetPeriod;
						else {
							Ch.Period = Ch.TargetPeriod;
							Ch.ArpeggioPeriod = 0;
						}
					}
				}
				if ((Ch.Effect == 14) && (((Ch.Para&0xF0)>>4) == 9))
                    Ch.Delay = Ch.Para&0xF;
                else
                    Ch.Delay = -1;
			}
		}

		i++;
	}

    End:
	UpdateChannelInfo();
}

#define Smp Samples[Ch.Sample]

static inline void MixAudio(int16_t *Buffer, uint32_t Pos) {
    int i = 0;
	int16_t OutL = 0;
	int16_t OutR = 0;
	float Result = 0;
	if (Playing) {
        while (i < NumOfChannels) {
            if (Ch.Sample != 32 && Ch.Period != 0) {

                Ch.VolFinal -= (Ch.VolFinal - Ch.VolFac)/VOLRAMPING_SPD;

                Ch.Pos += Ch.Delta;

                if (Smp.RepeatLeng > 2) {
                    while ((Ch.Pos>>INT_ACC) >= Smp.RepeatPoint + Smp.RepeatLeng) {
                        Ch.Pos -= Smp.RepeatLeng<<INT_ACC;
                        Ch.Looping = true;
                    }
                    if ((int32_t)(Ch.Pos>>INT_ACC) < (int32_t)Smp.RepeatPoint)
                        Ch.Looping = false;

                } else if ((Ch.Pos>>INT_ACC) >= Smp.Length) {
                    Ch.Sample = 32;
                }

                if (((Ch.Pos>>INT_ACC) <= Smp.Length) && (Ch.Sample != 32)) {
                    if (Interpolation) {
                        int8_t PrevData = 0;

                        if (((Ch.Pos>>INT_ACC) <= Smp.RepeatPoint) && Ch.Looping)
                            PrevData = SampleData[Smp.Addr + Smp.RepeatPoint + Smp.RepeatLeng - 1];
                        else if ((Ch.Pos>>INT_ACC) - 1 >= 0)
                            PrevData = SampleData[Smp.Addr + (Ch.Pos>>INT_ACC) - 1];

                        int32_t dy = SampleData[Smp.Addr + (Ch.Pos>>INT_ACC)] - PrevData;
                        float ix = (Ch.Pos/TOINT_SCL)-(Ch.Pos>>INT_ACC);

                        Result = (PrevData + dy*ix)*Ch.VolFinal;

                    } else Result = SampleData[Smp.Addr + (Ch.Pos>>INT_ACC)]*Ch.VolFinal;

                    Result = Result/(MIN(1.5, MAX(1, NumOfChannels/4)));

                    if (!Ch.Muted && Ch.VolFinal > 0.1) {
                        if (Ch.Pan != -1) {
                            float PanL = 1;
                            float PanR = 1;
                            if (Ch.Pan < 127)
                                PanR = 1 - (127 - Ch.Pan)/127.0*StereoSep;
                            else PanL = 1 - (Ch.Pan - 127.0)/128.0*StereoSep;
                            OutL += (int16_t)(Result*PanL);
                            OutR += (int16_t)(Result*PanR);
                        } else {
                            if ((i%4 == 0) || (i%4 == 3)) {
                                OutL += (int16_t)Result;
                                OutR += (int16_t)(Result*(1 - StereoSep));
                            } else {
                                OutR += (int16_t)Result;
                                OutL += (int16_t)(Result*(1 - StereoSep));
                            }
                        }
                    }
                } else Result = 0;
            } else {
                Ch.Pos = 0;
            }
            i ++ ;
        }
	}

	Buffer[Pos*2] = (OutL*MasterVol)/255;
	Buffer[Pos*2 + 1] = (OutR*MasterVol)/255;
}

static void FillBuffer(int16_t *Buffer) {
    int i = 0;

    StartTime = clock();

    while (i < BUFFER_SIZE) {
        if (Playing)
            Timer += TimePerSample;

        double TimePerTick = 2.5/Tempo;
        while (Timer >= TimePerTick) {
            NextTick();
            Timer -= TimePerTick;
        }

        MixAudio(Buffer, i);

        i ++ ;
    }

    EndTime = clock();
    ExcuteTime = (EndTime - StartTime)/CLOCKS_PER_SEC;
}

extern "C" __declspec(dllexport) char *MPGetSongName() {
    return SongName;
}

extern "C" __declspec(dllexport) double MPGetExcuteTime() {
    return ExcuteTime;
}

extern "C" __declspec(dllexport) uint32_t MPGetPos() {
    return (uint32_t)((CurrentPos<<16) | (Order[CurrentPos]<<8) | CurrentRow);
}

extern "C" __declspec(dllexport) void MPSetVolume(uint8_t Volume) {
    MasterVol = Volume;
}

extern "C" __declspec(dllexport) void MPSetInterpolation(bool UsingInterpolation = true)
{
    Interpolation = UsingInterpolation;
}

extern "C" __declspec(dllexport) void MPSetSeparation(float TargetStereoSep)
{
    StereoSep = TargetStereoSep;
}

extern "C" __declspec(dllexport) bool IsPlaying()
{
    return Playing;
}

//---------------------------------------------------------
//8bitbubsy's way to output audio

#include <windows.h>
#include <mmsystem.h>

static WAVEHDR WaveHeaders[2];
static uint8_t CurrentBuffer = 0;
static bool Running = true;
static HANDLE hThread, hAudioSem;
static HWAVEOUT hWave;

static void CALLBACK WaveOutputCallback(HWAVEOUT hWave, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2) {
    if (uMsg == WOM_DONE)
        ReleaseSemaphore(hAudioSem, 1, NULL);
}

static DWORD WINAPI MainThread(LPVOID lpParam) {
    WAVEHDR *WaveHeader;
    while (Running) {
        WaveHeader = &WaveHeaders[CurrentBuffer];
        FillBuffer((int16_t*)WaveHeader->lpData);
        waveOutWrite(hWave, WaveHeader, sizeof(WAVEHDR));
		CurrentBuffer = (CurrentBuffer + 1)%2;
        WaitForSingleObject(hAudioSem, INFINITE);
    }
    return 0;
}

extern "C" __declspec(dllexport) void MPStopModule(void) {
	int i;

	Running = false;

	if (hAudioSem != NULL)
		ReleaseSemaphore(hAudioSem, 1, NULL);

	if (hThread != NULL) {
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
		hThread = NULL;
	}

	if (hAudioSem != NULL) {
		CloseHandle(hAudioSem);
		hAudioSem = NULL;
	}

	if (hWave != NULL) {
		waveOutReset(hWave);

		i = 0;
		while (i < 2) {
			if (WaveHeaders[i].dwUser != 1)
				waveOutUnprepareHeader(hWave, &WaveHeaders[i], sizeof (WAVEHDR));
            i ++ ;
		}

		waveOutClose(hWave);
		hWave = NULL;
	}

	i = 0;
	while (i < 2) {
		if (SndBuffer[i] != NULL) {
			free(SndBuffer[i]);
			SndBuffer[i] = NULL;
		}
		i ++ ;
	}
}

extern "C" __declspec(dllexport) bool MPPlayModule() {

    DWORD ThreadID;
    int i = 0;
    CurrentBuffer = 0;
    Running = true;

    WAVEFORMATEX wfx;

    memset(WaveHeaders, 0, sizeof(WaveHeaders));

    memset(&wfx, 0, sizeof(wfx));
    wfx.nSamplesPerSec = SamplingRate;
    wfx.nChannels = 2;
    wfx.wBitsPerSample = 16;
    wfx.nBlockAlign = wfx.nChannels*(wfx.wBitsPerSample/8);
    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.cbSize = 0;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec*wfx.nBlockAlign;

//  HANDLE EmptyEvent = CreateEvent(NULL, 0, 0, NULL);
    if (waveOutOpen(&hWave, WAVE_MAPPER, &wfx, (DWORD_PTR)WaveOutputCallback, 0, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
		goto Err;

    if ((hAudioSem = CreateSemaphore(NULL, 1, 2, NULL)) == NULL)
        goto Err;

	while (i < 2) {
		SndBuffer[i] = (int16_t *)calloc(BUFFER_SIZE, wfx.nBlockAlign);
		if (SndBuffer[i] == NULL)
			goto Err;

        WaveHeaders[i].lpData = (LPSTR)SndBuffer[i];
        WaveHeaders[i].dwBufferLength = BUFFER_SIZE*wfx.nBlockAlign;
        WaveHeaders[i].dwUser = 1;
        WaveHeaders[i].dwFlags = WHDR_DONE;

		if (waveOutPrepareHeader(hWave, &WaveHeaders[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
			goto Err;

        i ++ ;
	}

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, NULL, 0, &ThreadID);
	if (hThread == NULL)
		goto Err;

    return true;

    Err:
    MPStopModule();
    return false;
}
