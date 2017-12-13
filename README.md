# Snake-game
Tema 2 – Snake
 
        	Modul in care jocul propus de mine raspunde la cerintele impuse:
1.  	Startul va fi impus de user in sensul ca acesta va trebui sa apese pe butonul de la joystick pentru a incepe jocul, care va porni dintr-o pozitie setata in cod. Initial, utilizatorul va fi primit cu un mesaj "Welcome!", urmat de mesajul "Press ok to start the game!" care va aparea in permanenta, atunci cand utilizatoul nu se joaca. De asemenea, pentru design, cand utilizatorul nu se joaca, dar jocul este conectat la curent, matricea va afisa un efect de fade. In momentul in care utilizatorul apasa pe joystick, mesajul de pe joystic va fi inlocuit cu scorul adunat pana in acel moment, efectul de fade se va opri si va fi inlocuit de jocul in sine.
2.  	Pe parcursul jocului, dupa ce sarpele mananca un mar, acesta va creste, iar scorul va fi afisat pe LCD pe tot parcursul jocului. Astfel jucatorul va sti in permanenta ce scor are.
3.   a. Scopul jocului este adunarea de cat mai multe mere. Odata cu mancarea unui mar, sarpele creste cu o unitate. Atunci cand sarpele devine suficient de mare este important ca acesta sa nu se loveasca de sine, orice lovire de sine va cauza pierderea jocului prin oprirea acestuia si afisarea pe LCD a mesajului "Game over!". (Orice lovire de sine a sarpelui echivareaza cu faptul ca acesta s-ar fi mancat singur)
     b.  Pe tot parcursul jocului scorul va fi afisat pe LCD, astfel ca utilizatorul va sti in permanenta ce scor are. O data cu mancarea unui mar, sarpele va creste cu o unitate iar viteza acestuia se va marii, dificultatea jocului constand chiar in viteza sarpelui. 
     Initial, sarpele are marimea de 2 unitati, jocul este considerat castigat in momentul in care marimea sarpelui atinge 60 de unitati. In acest caz, jocul va fi oprit iar ultilizatorul va putea citi pe LCD mesajul "YOU WON!" urmat de scorul castigat. In cazul in care un utilizator pierde jocul pana la adunarea celor 60 de mere, acesta va fi chestionat cu mesajul "Game over!".
4.   Dificultatea jocului consta in viteza sarpelui, care creste progresiv cu fiecare mar mancat. Astfel jocul poate fi jucat de orice tip de utilizator, deoarece, itinial sarpele are o viteza destul de mica. 

 Pentru acest proiect, pe langa matricea 8x8 de leduri, fire si placa Arduino, am folosit joystick-ul pentru controlul sarpelui. Fiecare inpout de la user va fi dat prin joystick. De asemenea am utilizat si LCD-ul pentru a afisa mesajele pentru utilizator precum si scorul.

 Video: https://drive.google.com/file/d/1W-_2hu65AsBaqiniVXIK7LqBBjmt2yxp/view?usp=sharing
