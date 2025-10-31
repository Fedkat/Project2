# Project 2 : Generaliseret fire-på-stribe spil

# Beskrivelse
Skriv et program der implementerer det klassiske spil 4 på stribe, men her i en version hvor spillepladestørrelse (Game size) og stribelængde (Line size) gives som input første gang spillet starter.
Derudover skal der implementeres en computer modspiller der tilfældigt vælger en ikke-fuld linie og indkaster brikken deri.
Som et alternativ til en computer modspiller, så skal der også implementeres funktionalitet til at håndtere en menneskelig modspiller.

Der skal laves en funktion kaldet `scan_settings` der spørger brugeren om
1) der spilles imod en computer,
2) hvor stor spillepladen er, og
3) hvor lang en vindende linie skal være.

Hele spillet drives herefter af funktionen `game_of_lines` hvori der allokeres ved brug af `malloc` plads nok til spillepladen i en variabel kaldet `arena`. 
Du får brug for følgende funktioner:
- `scan_move` funktion der spørger en given spiller om hvad deres næste træk er og tester om det er gyldigt,
  - hvis der spilles imod en computer kaldes `ai_move` i stedet; en funktion der returnere et tilfældigt men gyldigt næste træk,
- `update_arena` som opdaterer `arena` korrekt, 
- `print_arena` som udskriver vores `arena` til skærmen, og
- `winner` som tester om en af spillerne har vundet. 
  - `winner` returnere den vindende spiller eller `-1` hvis ingen spiller endnu har vundet. Alternativt kan du introducere en passende `enum` datatype til returværdien af `winner`.  

I filen [src/play_game.c](src/play_game.c) er der lavet en lille skabelon til den overordnede struktur af programmet - dette kan du frit benytte, ændre eller ignorere.
Det er oplagt at implementere funktionerne i et programbibliotek ved at definere prototyper i [src/game_of_lines.h](src/game_of_lines.h) og implementere funktionerne i [src/game_of_lines.c](src/game_of_lines.c). 
Det er også oplagt at teste funktionerne med unit test i [test/test_game_of_lines.c](test/test_game_of_lines.c). 

Her er et eksempel på en dialog med spillet - som dialogen kan se ud når du får skrevet dit program:

```shell
Play against computer (y/n)> y
Game size> 3
Line size> 3
___
___
___

Player 0 input a coordinate between 0 and 2> 0
___
___
0__

Computer 1 picked 0
___
1__
0__

Player 0 input a coordinate between 0 and 2> 2
___
1__
0_0

Computer 1 picked 1
___
1__
010

Player 0 input a coordinate between 0 and 2> 1
___
10_
010

Computer 1 picked 2
___
101
010

Player 0 input a coordinate between 0 and 2> 2
__0
101
010

Player 0 won!
```

Som altid skal du lave top-down programmering med trinvis forfinelse. 
Overvej omhyggeligt de anvendte kontrolstrukturer. 
Overvej også god brug af malloc (eller dynamisk stack allokering). 
Og sidst men ikke mindst, brug gode input- og output parametre i dine funktioner.


## HINT 1
For at implementere et 2D heap allokeret array kan man allokere som følger:
```c
int* arena = (int*)malloc(sizeof(int)*size_of_arena*size_of_arena); // the arena is quadratic, i.e. 
```
og introducere hjælpefunktionen
```c
int* get_cell(int* arena, int size_of_arena, int x, int y)
```

## HINT 2
Spillet skal stoppe når en vinder er fundet, men findes der altid en vinder? 

## Test
Skriv nogle unit test af funktionerne `update_arena` og `winner`.
Skabelonen er forberedt til at du kan bruge [mtest](https://github.com/MortenSchou/mtest) i filen [test/test_game_of_lines.c](test/test_game_of_lines.c).
Skriv også gerne unit test af de andre funktioner du introducerer gennem top-down programmering med trinvis forfinelse. 
