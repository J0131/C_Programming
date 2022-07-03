/********************************************************
* 파일목적 : 표준입력장치를 이용해 전자피아노를 구현하는프로그램
* 작성자 : 최범준
* final update : 2020-04-17
*********************************************************/

#include <conio.h> 
#include <stdio.h>
#include <Windows.h>
#include <iostream>

int mappingKey_to_Freq(char key, char alt); // 주파수를 반환해주는 함수


void main(void)
{
    int freq; 
    char ch, alt_on = 0;
    int duration = 100; // 100ms로 설정
    printf("\n          simple Electric Piano !!\n\n");
    printf(" 'A' - 'J' : octave 8 도 레 미 파 솔 라 시\n");
    printf(" 'Z' - 'M' : octave 7 도 레 미 파 솔 라 시 도\n");
    printf(" 'q' - 'i' : octave 6 도 레 미 파 솔 라 시 도\n");
    printf(" 'a' - 'k' : octave 5 도 레 미 파 솔 라 시 도\n");
    printf(" 'z' - 'm' : octave 4 도 레 미 파 솔 라 시\n");
    printf("\ninput next key :\n\n");
    while ((ch = _getch()) != 'ESC') // esc가 아닐경우 밑에 동작 실행
    {
        alt_on = 0;
        if (GetAsyncKeyState(VK_MENU) & 0x8000) // alt를 눌렀으면 alt_on을 1로저장
            alt_on = 1;
        freq = mappingKey_to_Freq(ch, alt_on); 
        if (freq != -1) {
            printf("input key (%c) : freq (%3d)\n", ch, freq);
            Beep(freq, duration); // 비프음 출력 함수 
        } // freq가 -1이 아니라면 if문안의 동작 실행
        else {
            printf("input key (%c) is wrong key input..\n", ch);
        } // freq가 -1이라면 오류메세지 출력
    }
}

int mappingKey_to_Freq(char key, char alt) // 각 문자를 입력받았을때 해당하는 키에맞는 주파수를 출력하게만드는 함수
{
    int freq;
    if ((key == 'z') && (alt == 0)) 
    {
        freq = 262; printf("Octave 4 - 도(C), 261.63 Hz\n");
    }
    else if ((key == 'z') && (alt == 1))
    {
        freq = 277; printf("Octave 4 - 도# (C#), 277.18 Hz\n");
    }
    else if ((key == 'x') && (alt == 0))
    {
        freq = 294; printf("Octave 4 - 레(D), 293.66 Hz\n");
    }
    else if ((key == 'x') && (alt == 1))
    {
        freq = 311; printf("Octave 4 - 레#(D#), 311.12 Hz\n");
    }
    else if ((key == 'c') && (alt == 0))
    {
        freq = 330; printf("Octave 4 - 미(E), 329.62 Hz\n");
    }
    else if ((key == 'c') && (alt == 1))
    {
        freq = -1;
    }
    else if ((key == 'v') && (alt == 0))
    {
        freq = 349; printf("Octave 4 - 파(F), 349.22 Hz\n");
    }
    else if ((key == 'v') && (alt == 1))
    {
        freq = 370; printf("Octave 4 - 파#(F#), 369.99 Hz\n");
    }
    else if ((key == 'b') && (alt == 0))
    {
        freq = 392; printf("Octave 4 - 솔(G), 391.99 Hz\n");
    }
    else if ((key == 'b') && (alt == 1))
    {
        freq = 415; printf("Octave 4 - 솔#(G#), 415.30 Hz\n");
    }
    else if ((key == 'n') && (alt == 0))
    {
        freq = 440; printf("Octave 4 - 라(A), 440.00 Hz\n");
    }
    else if ((key == 'n') && (alt == 1))
    {
        freq = 466; printf("Octave 4 - 라#(A#), 466.16 Hz\n");
    }
    else if ((key == 'm') && (alt == 0))
    {
        freq = 494; printf("Octave 4 - 시(B), 493.88 Hz\n");
    }
    else if ((key == 'm') && (alt == 1))
    {
        freq = -1; 
    } // 4 옥타브

    if ((key == 'a') && (alt == 0))
    {
        freq = 523; printf("Octave 5 - 도(C), 523.25 Hz\n");
    }
    else if ((key == 'a') && (alt == 1))
    {
        freq = 554; printf("Octave 5 - 도# (C#), 554.36 Hz\n");
    }
    else if ((key == 's') && (alt == 0))
    {
        freq = 587; printf("Octave 5 - 레(D), 587.32 Hz\n");
    }
    else if ((key == 's') && (alt == 1))
    {
        freq = 622; printf("Octave 5 - 레#(D#), 622.25 Hz\n");
    }
    else if ((key == 'd') && (alt == 0))
    {
        freq = 659; printf("Octave 5 - 미(E), 659.25 Hz\n");
    }
    else if ((key == 'd') && (alt == 1))
    {
        freq = -1;
    }
    else if ((key == 'f') && (alt == 0))
    {
        freq = 698; printf("Octave 5 - 파(F), 698.45 Hz\n");
    }
    else if ((key == 'f') && (alt == 1))
    {
        freq = 740; printf("Octave 5 - 파#(F#), 739.98 Hz\n");
    }
    else if ((key == 'g') && (alt == 0))
    {
        freq = 784; printf("Octave 5 - 솔(G), 783.99 Hz\n");
    }
    else if ((key == 'g') && (alt == 1))
    {
        freq = 831; printf("Octave 5 - 솔#(G#), 830.60 Hz\n");
    }
    else if ((key == 'h') && (alt == 0))
    {
        freq = 880; printf("Octave 5 - 라(A), 880.00 Hz\n");
    }
    else if ((key == 'h') && (alt == 1))
    {
        freq = 932; printf("Octave 5 - 라#(A#), 932.32 Hz\n");
    }
    else if ((key == 'j') && (alt == 0))
    {
        freq = 988; printf("Octave 5 - 시(B), 987.76 Hz\n");
    }
    else if ((key == 'j') && (alt == 1))
    {
        freq = -1;
    }
    else if ((key == 'k') && (alt == 0))
    {
        freq = 1047; printf("Octave 6 - 도(C), 1046.50 Hz\n");
    } // 5 옥타브

    if ((key == 'q') && (alt == 0))
    {
        freq = 1047; printf("Octave 6 - 도(C), 1046.50 Hz\n");
    }
    else if ((key == 'q') && (alt == 1))
    {
        freq = 1109; printf("Octave 6 - 도# (C#), 1108.73 Hz\n");
    }
    else if ((key == 'w') && (alt == 0))
    {
        freq = 1175; printf("Octave 6 - 레(D), 1174.65 Hz\n");
    }
    else if ((key == 'w') && (alt == 1))
    {
        freq = 1245; printf("Octave 6 - 레#(D#), 1244.50 Hz\n");
    }
    else if ((key == 'e') && (alt == 0))
    {
        freq = 1329; printf("Octave 6 - 미(E), 1318.51 Hz\n");
    }
    else if ((key == 'e') && (alt == 1))
    {
        freq = -1;
    }
    else if ((key == 'r') && (alt == 0))
    {
        freq = 1397; printf("Octave 6 - 파(F), 1396.91 Hz\n");
    }
    else if ((key == 'r') && (alt == 1))
    {
        freq = 1480; printf("Octave 6 - 파#(F#), 1479.97 Hz\n");
    }
    else if ((key == 't') && (alt == 0))
    {
        freq = 1568; printf("Octave 6 - 솔(G), 1567.98 Hz\n");
    }
    else if ((key == 't') && (alt == 1))
    {
        freq = 1661; printf("Octave 6 - 솔#(G#), 1661.21 Hz\n");
    }
    else if ((key == 'y') && (alt == 0))
    {
        freq = 1760; printf("Octave 6 - 라(A), 1760.00 Hz\n");
    }
    else if ((key == 'y') && (alt == 1))
    {
        freq = 1865; printf("Octave 6 - 라#(A#), 1864.65 Hz\n");
    }
    else if ((key == 'u') && (alt == 0))
    {
        freq = 1976; printf("Octave 6 - 시(B), 1975.53 Hz\n");
    }
    else if ((key == 'u') && (alt == 1))
    {
        freq = -1;
    }
    else if ((key == 'i') && (alt == 0))
    {
        freq = 2093; printf("Octave 7 - 도(C), 2093.005 Hz\n");
    } // 6 옥타브

    if ((key == 'Z') && (alt == 0))
    {
        freq = 2093; printf("Octave 7 - 도(C), 2093.005 Hz\n");;
    }
    else if ((key == 'Z') && (alt == 1))
    {
        freq = 2217; printf("Octave 7 - 도# (C#), 2217.46 Hz\n");
    }
    else if ((key == 'X') && (alt == 0))
    {
        freq = 2349; printf("Octave 7 - 레(D), 2349.31 Hz\n");
    }
    else if ((key == 'X') && (alt == 1))
    {
        freq = 2489; printf("Octave 7 - 레#(D#), 2489.01 Hz\n");
    }
    else if ((key == 'C') && (alt == 0))
    {
        freq = 2637; printf("Octave 7 - 미(E), 2637.02 Hz\n");
    }
    else if ((key == 'C') && (alt == 1))
    {
        freq = -1;
    }
    else if ((key == 'V') && (alt == 0))
    {
        freq = 2794; printf("Octave 7 - 파(F), 2793.82 Hz\n");
    }
    else if ((key == 'V') && (alt == 1))
    {
        freq = 2660; printf("Octave 7 - 파#(F#), 2959.95 Hz\n");
    }
    else if ((key == 'B') && (alt == 0))
    {
        freq = 3136; printf("Octave 7 - 솔(G), 3135.96 Hz\n");
    }
    else if ((key == 'B') && (alt == 1))
    {
        freq = 3322; printf("Octave 7 - 솔#(G#), 3322.43 Hz\n");
    }
    else if ((key == 'N') && (alt == 0))
    {
        freq = 3520; printf("Octave 7 - 라(A), 3520.00 Hz\n");
    }
    else if ((key == 'N') && (alt == 1))
    {
        freq = 3729; printf("Octave 7 - 라#(A#), 3729.31 Hz\n");
    }
    else if ((key == 'M') && (alt == 0))
    {
        freq = 3951; printf("Octave 7 - 시(B), 3951.06 Hz\n");
    }
    else if ((key == 'M') && (alt == 1))
    {
        freq = -1;
    } // 7 옥타브
   

    if ((key == 'A') && (alt == 0))
    {
        freq = 4186; printf("Octave 8 - 도(C), 4186.00 Hz\n");
    }
    else if ((key == 'A') && (alt == 1))
    {
        freq = 4435; printf("Octave 8 - 도# (C#), 4434.92 Hz\n");
    }
    else if ((key == 'S') && (alt == 0))
    {
        freq = 4699; printf("Octave 8 - 레(D), 4698.63 Hz\n");
    }
    else if ((key == 'S') && (alt == 1))
    {
        freq = 4978; printf("Octave 8 - 레#(D#), 4978.03 Hz\n");
    }
    else if ((key == 'D') && (alt == 0))
    {
        freq = 5274; printf("Octave 8 - 미(E), 5274.04 Hz\n");
    }
    else if ((key == 'D') && (alt == 1))
    {
        freq = -1;
    }
    else if ((key == 'F') && (alt == 0))
    {
        freq = 5588; printf("Octave 8 - 파(F), 5587.65 Hz\n");
    }
    else if ((key == 'F') && (alt == 1))
    {
        freq =5920; printf("Octave 8 - 파#(F#), 5919.91 Hz\n");
    }
    else if ((key == 'G') && (alt == 0))
    {
        freq = 6272; printf("Octave 8 - 솔(G), 6271.92 Hz\n");
    }
    else if ((key == 'G') && (alt == 1))
    {
        freq = 6645; printf("Octave 8 - 솔#(G#), 6644.87 Hz\n");
    }
    else if ((key == 'H') && (alt == 0))
    {
        freq = 7040; printf("Octave 8 - 라(A), 7040.00 Hz\n");
    }
    else if ((key == 'H') && (alt == 1))
    {
        freq = 7459; printf("Octave 8 - 라#(A#), 7458.62 Hz\n");
    }
    else if ((key == 'J') && (alt == 0))
    {
        freq = 7902; printf("Octave 8 - 시(B), 7902.13 Hz\n");
    }
    else if ((key == 'J') && (alt == 1))
    {
        freq = -1;
    }

    return freq;
 
}


